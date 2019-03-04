#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

#include "filehelp.h"
#include "fileop.h"


int fileop_open(const char *filename, long size, bool src) {
    int fd;

    if (src) {
        if ((fd = open(filename, 0)) < 0)
            printf ("Error: Failed to open file %s(%ld), err: %s\n", filename, size, strerror(errno));
    }
    else {
        if ((fd = open(filename, O_CREAT|O_WRONLY, 0666)) < 0)
            printf ("Error: Failed to open file %s(%ld), err: %s\n", filename, size, strerror(errno));
    }
    return fd;
}

int fileop_close(int fd) {
    if (close(fd) < 0) {
        printf ("Failed to close fd\n");
        return -1;
    }
    return 0;
}

int fileop_copy(int srcfd, int dstfd, long size) {
    int pagesize = getpagesize(), i = 0;
    long scpy;
    unsigned char *copy_buf;

    if (pagesize < 0) {
        printf ("Error: pagesize negative\n");
        return -1;
    }

    copy_buf = (unsigned char*)malloc(pagesize);

    if (copy_buf == NULL) {
        printf ("Error: malloc(%d) failed\n", pagesize);
        return -1;
    }
    errno = 0;
    while (size > 0) {
        scpy = (size > pagesize ? pagesize : size);
        if (read(srcfd, copy_buf, scpy) != scpy) {
            printf ("Error: failed to read from src file(%s)\n.", strerror(errno));
            free(copy_buf);
            return -1;
        }
        if (write(dstfd, copy_buf, scpy) != scpy) {
            printf ("Error: failed to write to dst file %d(%s)\n", dstfd, strerror(errno));
            free(copy_buf);
            return -1;
        }
        size -= scpy;
        i++;
    }

    printf ("Copied in %d loops with pagesize %d", i, pagesize);

    free(copy_buf);
    return 0;
}
