
#include <stdio.h>
#include "../declare/myfile.h"

fsd_t test_init_fs(int blockCount, int mode) {
    printf("creating a %d bytes (%d megabytes) disk\n", blockCount * BLOCK_SIZE_IN_BYTE, blockCount * BLOCK_SIZE_IN_BYTE / 1024 / 1024);
    printf("the virtual disk file size should be %d bytes\n",
           sizeof(long) * 2 +
           blockCount * sizeof(char) +
           blockCount * INODE_SIZE_IN_BYTE +
           blockCount * BLOCK_SIZE_IN_BYTE);
    fsd_t ret = init_fs("Z:\\tmp.fs", blockCount, FS_ONCE);
    return ret;
}

int main() {
    close_fs(test_init_fs(131072, FS_ONCE));
    printf("press enter to quit");
    getc(stdin);
    return 0;
}