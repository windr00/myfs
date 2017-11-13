//
// Created by windr on 17-11-11.
//

#include "fs.h"

#define O_RDONLY 0 //read only
#define O_WRONLY 1 //write only
#define O_RDWR 2 // read & write
#define O_APPEND 3 //append to the end on write
#define O_CREATE 4 // create if non-exist
#define FS_LAZY 0 //dynamicly grow disk file space
#define FS_ONCE 1 //grow disk file space immediately
typedef int fsd_t;
typedef int fd_t;

fsd_t load_fs(const char *fspath);

fsd_t init_fs(const char *fspath, long blockCount, int mode);

fd_t /*mem_fd*/ f_open(fsd_t fsd, const char *pathname, int oflag, ...);

int f_close(fsd_t fsd, fd_t fd);

int close_fs(fsd_t fsd);

long f_read(fsd_t fsd, fd_t fd, void *buf, long count);

long f_write(fsd_t fsd, fd_t fd, void *buf, long count);

int unlink_f(fsd_t fsd, const char *pathname);

dentry *diropen(fsd_t fsd, const char *path);

dentry *dirread(fsd_t fsd, dentry *dir);

