//
// Created by windr on 17-11-11.
//

#ifndef MYFS_OPERATOR_H
#define MYFS_OPERATOR_H

#include "inode.h"

typedef struct {

    int fd;

    const char * openedFileName;

    int oflag;

    int currentOffset;

    inode * currentINode;

    dentry * parentDentry;
}foperator;

#endif //MYFS_OPERATOR_H
