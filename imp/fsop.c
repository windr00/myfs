//
// Created by windr on 17-11-11.
//
#include "myfile.c"
#include "fs.h"
#include "dirdata.h"

static fs * openedFileSystem;

int fsCount = 0;


fs * resize_fs_array() {
    if (openedFileSystem == NULL) {
        openedFileSystem = (fs *)malloc(sizeof(fs));
        openedFileSystem->handler = fsCount;
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


int load_fs(const char *fspath) {

}

int init_fs(const char * fspath, long blockCount, int mode) {
    FILE * diskFile = fopen(fspath, "wb");
    if (diskFile == NULL) {
        return -1;
    }
    fs * newFs = resize_fs_array();
    newFs->blockCount = blockCount;
    newFs->fd = 0;
    newFs->mode = mode;
    newFs->diskFileName = fspath;
    newFs->bitMap = (unsigned char *)malloc(sizeof(blockCount * BLOCK_SIZE_IN_BYTE));
    newFs->operatorList = NULL;
    fprintf(diskFile, "%ld", blockCount);
    newFs->bitmapOffset = ftell(newFs);
    for (long i = 0; i < blockCount; i ++) {
        fprintf(diskFile, "%c", newFs->bitMap[i]);
    }
    newFs->blockSectorOffset = ftell(newFs);

    dirdata data;
    data.childCount = 0;
    data.childName = NULL;
    data.childNodes = NULL;
    data.fileTypes = NULL;

    inode root;
    root.blockCount = blockCount;
    root.linkCount = 1;
    root.num = 0;
    root.lastBlockSize = sizeof(data);
    root.directLinkedBlock[0] =
    dentry * head = (dentry *)malloc(sizeof(dentry));
    head->children = NULL;
    head->childrenCount = 0;
    head->fileName = "/";
    head->parent = NULL;
    head->nodeNum = 0;

    for (long i = 0; i < blockCount; i++) {

    }
}

int close_fs(int fsd) {

}