//
// Created by windr on 17-11-11.
//
#include <stdio.h>
#include <malloc.h>
#include <mem.h>
#include "myfile.c"
#include "../declare/dirdata.h"
#include "../declare/errnum.h"

static fs * openedFileSystem;

int fsCount = 0;

fs * resize_fs_array() {
    if (openedFileSystem == NULL) {
        openedFileSystem = (fs *)malloc(sizeof(fs));
        openedFileSystem->mem_fsd = fsCount;
        openedFileSystem->disk_validInodeCount = 1;
        openedFileSystem->disk_inodeCache = (inode *) malloc(sizeof(inode));
        fsCount++;
        return  openedFileSystem + (fsCount - 1);
    }

    fs * temp = (fs *)malloc(sizeof(fs) * (fsCount + 1));
    memcpy(temp, openedFileSystem, sizeof(fs) * (fsCount));
    free(openedFileSystem);
    openedFileSystem = temp;
    fsCount++;
    return openedFileSystem + (fsCount - 1);
};

int find_first_empty_block(fs *file) {
    for (int i = 0; i < file->disk_blockCount; i++) {
        if (file->disk_bitMap[i] == BLOCK_FLAG_EMPTY) {
            return i;
        }
    }
    return VIRTUAL_DISK_FULL_ERROR;
}

int find_last_empty_block(fs * file) {
    int empty = VIRTUAL_DISK_FULL_ERROR;
    for (int i = 0; i < file->disk_blockCount; i++) {
        if (file->disk_bitMap[i] == BLOCK_FLAG_EMPTY) {
            empty = i;
        }
    }
    return empty;
}

int expand_disk_size(fs *file, long block_index) {
    fseek(file->mem_fd, file->mem_blockSectorOffset, 0);
    char block[BLOCK_SIZE_IN_BYTE] = {0};
    int i = find_last_empty_block(file);
    if (i == VIRTUAL_DISK_FULL_ERROR) {
        return VIRTUAL_DISK_FULL_ERROR;
    }
    for (i; i < block_index; i++) {
        fwrite(block, BLOCK_SIZE_IN_BYTE, 1, file->mem_fd);
    }
    return VIRTUAL_DISK_OPERATION_SUCCESS;
}

int write_block(fs *file, long size, void *memory, long blockIndex) {
    if (file->disk_mode == FS_LAZY) {
        int ret = expand_disk_size(file, blockIndex);
        if (ret != VIRTUAL_DISK_OPERATION_SUCCESS) {
            return ret;
        }
    }
    fseek(file->mem_fd, file->mem_blockSectorOffset + blockIndex * BLOCK_SIZE_IN_BYTE, 0);
    fwrite(memory, sizeof(unsigned char), (size_t) size, file->mem_fd);
    file->disk_bitMap[blockIndex] = BLOCK_FLAG_TAKEN;
    return VIRTUAL_DISK_OPERATION_SUCCESS;
}

fsd_t load_fs(const char *fspath) {

}

int write_inode(fs *file, inode *cache, int validInodeCount) {
    fseek(file->mem_fd, file->mem_inodeSectorOffset, 0);
    fwrite(cache, INODE_SIZE_IN_BYTE, (size_t) validInodeCount, file->mem_fd);
    char tmp[INODE_SIZE_IN_BYTE] = {0};
    for (int i = 0; i < (file->disk_blockCount / INODE_BLOCK_SCALAR) - validInodeCount; i++) {
        fwrite(tmp, INODE_SIZE_IN_BYTE, 1, file->mem_fd);
    }
    return VIRTUAL_DISK_OPERATION_SUCCESS;
}

int write_fs_info(fs *newFs) {
    fseek(newFs->mem_fd, 0, 0);
    fprintf(newFs->mem_fd, "%ld%ld", newFs->disk_blockCount, newFs->disk_validInodeCount);
    newFs->mem_bitmapOffset = ftell(newFs->mem_fd);
    fwrite(newFs->disk_bitMap, sizeof(char), (size_t) newFs->disk_blockCount, newFs->mem_fd);
    newFs->mem_inodeSectorOffset = ftell(newFs->mem_fd);
    write_inode(newFs, newFs->disk_inodeCache, newFs->disk_validInodeCount);
    fseek(newFs->mem_fd, newFs->disk_blockCount * INODE_SIZE_IN_BYTE, newFs->mem_inodeSectorOffset);
    newFs->mem_blockSectorOffset = ftell(newFs->mem_fd);
    return VIRTUAL_DISK_OPERATION_SUCCESS;
}

fsd_t init_fs(const char *fspath, long blockCount, int mode) {
    fs * newFs = resize_fs_array();
    newFs->disk_blockCount = blockCount;
    newFs->mem_fd = fopen(fspath, "wb");
    if (newFs->mem_fd == NULL) {
        return VIRTUAL_DISK_FILE_WRITE_ERROR;
    }
    newFs->disk_mode = mode;
    newFs->mem_diskFileName = fspath;
    newFs->disk_bitMap = (unsigned char *) malloc(blockCount);
    memset(newFs->disk_bitMap, BLOCK_FLAG_EMPTY, blockCount);
    newFs->mem_operatorList = NULL;
    write_fs_info(newFs);
    if (mode == FS_ONCE) {
        expand_disk_size(newFs, blockCount - 1);
//        char block[BLOCK_SIZE_IN_BYTE] = {0};
//        for (long i = 0; i < blockCount; i++) {
//            fwrite(block, BLOCK_SIZE_IN_BYTE, 1, newFs->mem_fd);
//        }
    }
    dirdata data;
    data.childCount = 0;
    data.childName = NULL;
    data.childNodes = NULL;
    data.fileTypes = NULL;

    inode *root = newEmptyInode();
    dentry * head = (dentry *)malloc(sizeof(dentry));
    head->children = NULL;
    head->childrenCount = 0;
    head->fileName = "/";
    head->parent = NULL;
    head->nodeNum = 0;

    root->lastBlockSize = sizeof(data);
    root->directLinkedBlock[root->lastBlockIndex] = find_first_empty_block(newFs);
    newFs->built_dirEntryHead = head;
    newFs->disk_inodeCache = root;
    int ret = write_block(newFs, sizeof(data), &data, root->directLinkedBlock[root->lastBlockIndex]);
    if (ret != VIRTUAL_DISK_OPERATION_SUCCESS) {
        fclose(newFs->mem_fd);
        free(newFs);
        free(root);
        free(head);
        return ret;
    }
    return newFs->mem_fsd;
}

int close_fs(fsd_t fsd) {
    fs *file = openedFileSystem + fsd;
    int ret = write_fs_info(file);
    ret &= fclose(file->mem_fd);
    if (ret) {
        free(&openedFileSystem[fsd]);
        return VIRTUAL_DISK_FILE_CLOSE_ERROR;
    }
    free(&openedFileSystem[fsd]);
    return VIRTUAL_DISK_OPERATION_SUCCESS;
}