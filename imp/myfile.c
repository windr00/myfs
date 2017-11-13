//
// Created by windr on 17-11-11.
//

#include <string.h>
#include <stdlib.h>
#include "../declare/myfile.h"
#include "../declare/global.h"
#include "../declare/errnum.h"

fs *find_file_system(fsd_t fsd) {
    return global_openedFileSystem + fsd;
}

/**
 * get the seperated path names stored in a string array
 * @param pathname
 * @param count
 * @return free required
 */
const char **get_seperate_path(const char *pathname, int * /* return */ count) {
    if (pathname[0] != '/') {
        return NULL;
    }
    char **array = NULL;
    int arrayCount = 0;
    int start = 1;
    int end = 0;
    for (int i = 1; i < strlen(pathname); i++) {
        if (pathname[i] == '/') {
            end = i - 1;
            char **tmp = array;
            array = (char **) malloc(sizeof(char *) * (arrayCount + 1));
            memcpy(array, tmp, sizeof(char *), arrayCount);
            memcpy(array[arrayCount++], pathname + start, sizeof(char), end - start);

        }
    }
}

fd_t /*mem_fd*/ f_open(fsd_t fsd, const char *pathname, int oflag, ...) {
    fs *disk = find_file_system(fsd);
    if (disk == NULL) {
        return VIRTUAL_DISK_NOT_EXIST_ERORR;
    }

}

int f_close(fsd_t fsd, fd_t fd) {

}

long f_read(fsd_t fsd, fd_t fd, void *buf, long count) {

}

long f_write(fsd_t fsd, fd_t fd, void *buf, long count) {

}

int unlink_f(fsd_t fsd, const char *pathname) {

}

dentry *diropen(fsd_t fsd, const char *path) {

}

dentry *dirread(fsd_t fsd, dentry *dir) {

}