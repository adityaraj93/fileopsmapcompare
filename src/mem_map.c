#include <stdio.h>
#include <stdbool.h>

#include "mem_map.h"

int map_open(const char *filename, long size, bool is_src) {
    (void) filename;
    (void)size;
    (void)is_src;

    return 0;
}

int map_copy(int srcfd, int dstfd, long size) {
    srcfd = srcfd + dstfd + (int)size;
    return 0;
}

int map_close(int fd) {
    (void) fd;
    return 0;
}
