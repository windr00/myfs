//
// Created by windr on 17-11-11.
//

#ifndef MYFS_DENTRY_H
#define MYFS_DENTRY_H

#define FILENAME_END_CHAR 0

#define ENTRY_DIR 0;
#define ENTRY_FILE 1;


typedef struct _dentry_ {

    struct _dentry_ * parent;

    const char * fileName;

    int nodeNum;

    int childrenCount;

    struct _dentry_ ** children;

}dentry;

#endif //MYFS_DENTRY_H
