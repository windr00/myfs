//
// Created by windr on 17-11-11.
//

#ifndef MYFS_INODE_H
#define MYFS_INODE_H
#include "dentry.h"

#define DIRECT_BLOCK_COUNT       1024;
#define SECOND_LEVEL_BLOCK_COUNT 256;
#define THIRD_LEVEL_BLOCK_COUNT  64;

#define INODE_SIZE_IN_BYTE (sizeof(int) * 4 + sizeof(long) * (DIRECT_BLOCK_COUNT + SECOND_LEVEL_BLOCK_COUNT + THIRD_LEVEL_BLOCK_COUNT))

typedef struct _inode_{

    int num;

    int linkCount;

    int lastBlockSize;

    long blockCount;

    long directLinkedBlock[DIRECT_BLOCK_COUNT];

    long secondLevelLinkedBlock[SECOND_LEVEL_BLOCK_COUNT];

    long thirdLevelLinkedBlock[THIRD_LEVEL_BLOCK_COUNT];

}inode;

inode * newEmptyInode();



#endif //MYFS_INODE_H
