//
// Created by windr on 17-11-11.
//

#ifndef MYFS_DIRDATA_H
#define MYFS_DIRDATA_H
typedef struct _dirdata_{

    int childCount;

    int * childNodes;

    const char * childName;

    char * fileTypes;

}dirdata;
#endif //MYFS_DIRDATA_H
