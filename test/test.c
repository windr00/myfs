
#include <stdio.h>
#include "../declare/myfile.h"

int main() {
    const char *path = "Z:\\tmp.fs";
    int handler = init_fs("Z:\\tmp.fs", 100, FS_ONCE);
    printf("created file system at %s\n with handler %d", path, handler);
    close_fs(handler);
    return 0;
}