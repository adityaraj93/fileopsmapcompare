#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "filehelp.h"

/* check if the file exists and is a regular file */
bool file_exists(const char *filename) {
    struct stat st;

    errno = 0;
    if (stat(filename, &st)) {
        printf("Error: Failed to access file %s, err: %s\n", filename, strerror(errno));
        return false;
    }
    if (S_ISREG(st.st_mode))
        return true;
    else
        return false;
}

long file_size(const char *filename) {
    struct stat st;

    if (stat(filename, &st)) {
        printf("Error: Failed to access file %s, err: %s\n", filename, strerror(errno));
        return -1;
    }

    return st.st_size;
}

long file_size_fd(int fd) {
    struct stat st;

    if (fstat(fd, &st)) {
        printf("Error: Failed to access file, err %s\n", strerror(errno));
        return -1;
    }
    return st.st_size;
}
