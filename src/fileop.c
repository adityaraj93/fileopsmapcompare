#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "filehelp.h"
#include "fileop.h"

int use_fileops(const char *srcfile, const char *dstfile) {

    if (!file_exists(srcfile)) {
        printf("Invalid file %s", srcfile);
        return -1;
    }
    (void)dstfile;
    return 0;
}

