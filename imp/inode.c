//
// Created by windr on 17-11-11.
//
#include <stdlib.h>
#include <memory.h>
#include "inode.h"

inode * newEmptyInode() {
    inode * node = (inode *)malloc(sizeof(inode));
    memset(node->directLinkedBlock,0, sizeof(long));

}
