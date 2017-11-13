
#include <stdio.h>
#include "../declare/myfile.h"

int main() {
    const char *path = "Z:\\tmp.fs";
    int handler = init_fs("Z:\\tmp.fs", 131072 /*262144*/, FS_LAZY);
    printf("created file system at %s\n with handler %d", path, handler);
    close_fs(handler);
    return 0;
}