//
// Created by windr on 17-11-11.
//
#include <stdlib.h>
#include "../declare/inode.h"

inode * newEmptyInode() {
    inode * node = (inode *)malloc(sizeof(inode));
    for (int i = 0; i < DIRECT_BLOCK_COUNT; i++) {
        node->directLinkedBlock[i] = -1;
        if (i < SECOND_LEVEL_BLOCK_COUNT) {
            node->secondLevelLinkedBlock[i] = -1;
        }
        if (i < THIRD_LEVEL_BLOCK_COUNT) {
            node->thirdLevelLinkedBlock[i] = -1;
        }
    }
    node->blockCount = 0;
    node->lastBlockSize = 0;
    node->linkCount = 1;
    node->num = 0;
    node->lastBlockIndex = 0;
    return node;
}
