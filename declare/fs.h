//
// Created by windr on 17-11-11.
//

#ifndef MYFS_FS_H
#define MYFS_FS_H

#include "foperator.h"
#include "stdio.h"
#include "myfile.h"

#define BLOCK_SIZE_IN_BYTE 4096
#define BLOCK_FLAG_EMPTY 0
#define BLOCK_FLAG_TAKEN 1

/**
 * file system structure
 */
typedef struct {

    /**
     * user handler to access this disk's file system
     * <br>
     * only stored in memory
     */
    fsd_t mem_fsd;

    /**
     * user handlers to access files on the disk
     * <br>
     * only stored in memory (free required)
     */
    foperator *mem_operatorList;

    /**
     * the path for the file to store the disk
     * <br>
     * only stored in memory (free not required)
     */
    const char *mem_diskFileName;

    /**
     * the storage policy for the disk file
     * <br>
     * stored in disk
     */
    int disk_mode;

    /**
     * the count of foperator
     * <br>
     * only stored in memory
     */
    int mem_operatorCount;

    /**
     * the bitmap to show the usage of disk blocks
     * <br>
     * stored in disk
     */
    unsigned char *disk_bitMap;

    /**
     * the count of the total blocks on the disk
     * <br>
     * stored in disk
     */
    long disk_blockCount;

    /**
     * the count of the inodes that are in use
     * <br>
     * stored in disk
     */
    long disk_validInodeCount;

    /**
     * the FILE handler to access the disk file
     * <br>
     * stored only in memory (fclose required)
     */
    FILE *mem_fd;

    /**
     * current disk file offset start from blockSectorOffset
     * </br>
     * stored only in memory
     */
    long mem_currentOffset;

    /**
     * the offset of the bitmap sector of the disk file
     * <br>
     * stored only in memory
     */
    long mem_bitmapOffset;

    /**
     * the offset of the inode sector of the disk file
     * <br>
     * stored only in memory
     */
    long mem_inodeSectorOffset;

    /**
     * the offset of the block sector of the disk file
     * <br>
     * stored only in memory
     */
    long mem_blockSectorOffset;

    /**
     * the root of directory tree
     * <br>
     * stored in disk block, built in memory (write on free required)
     */
    dentry *built_dirEntryHead;

    /**
     * the array of all the inodes
     * <br>
     * stored in disk (free required)
     */
    inode *disk_inodeCache;

} fs;
#endif //MYFS_FS_H
