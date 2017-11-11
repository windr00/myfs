//
// Created by windr on 17-11-11.
//

#ifndef MYFS_FS_H
#define MYFS_FS_H

#include "foperator.h"
#include "dirent.h"

#define BLOCK_SIZE_IN_BYTE 4096

typedef struct {

    int handler;

    foperator * operatorList;

    const char * diskFileName;

    int mode;

    int operatorCount;

    unsigned char * bitMap;

    long blockCount;

    FILE * fd;

    long currentOffset;

    long bitmapOffset;

    long inodeSectorOffset;

    long blockSectorOffset;

    dentry * dirEntryHead;

}fs;
#endif //MYFS_FS_H
