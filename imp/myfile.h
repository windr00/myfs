//
// Created by windr on 17-11-11.
//

#include <stdio.h>
#include <dirent.h>
#include "fs.h"

#ifndef MYFS_MYFILE_H
#define MYFS_MYFILE_H
#define O_RDONLY 0 //read only
#define O_WRONLY 1 //write only
#define O_RDWR 2 // read & write
#define O_APPEND 3 //append to the end on write
#define O_CREATE 4 // create if non-exist
#define BLOCK_SIZE 4096
#define FS_LAZY 0 //dynamicly grow disk file space
#define FS_ONCE 1 //grow disk file space immediately


int load_fs(const char *fspath);

int init_fs(const char *fspath, long blockCount, int mode)

int /*fd*/ open(const char * pathname, int oflag, ...);

int close(int fd);

int close_fs(int fsd);

long read(int fd, void * buf, long count);

long write(int fd, void * buf, long count);

int unlink (const char * pathname);

DIR * diropen(const char * path);


struct direnh * dirread(DIR * dir);
#endif //MYFS_MYFILE_H
