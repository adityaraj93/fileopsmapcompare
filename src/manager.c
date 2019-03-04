#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "manager.h"
#include "filehelp.h"
#include "fileop.h"
#include "timeprofile.h"
#include "mem_map.h"

static int (*open_file)(const char *filename, long size, bool is_src);
static int (*copy_file)(int srcfd, int dstfd, long size);
static int (*close_file)(int fd);

static void init_fps(enum op_mode opmode) {
    switch (opmode) {
        case OP_MD_FILEOP:
            open_file = fileop_open;
            copy_file = fileop_copy;
            close_file = fileop_close;
            break;

        case OP_MD_MMAP:
            open_file = map_open;
            copy_file = map_copy;
            close_file = map_close;
            break;
    }
}

int manage(enum op_mode opmode, const char *srcfile, const char *dstfile) {
    long src_size;
    int srcfd, dstfd;
    struct timeprofile tp;

    memset(&tp, 0, sizeof(tp));
    timeit(&tp, TP_START);

    if (!file_exists(srcfile)) {
        printf ("Error: Unable to access file : %s, err: %s\n", srcfile, strerror(errno));
        return -1;
    }

    // initialize fps
    init_fps(opmode);

    if ((src_size = file_size(srcfile)) < 0) {
        printf ("Error: Unable to get size of srcfile %s, err: %s\n", srcfile, strerror(errno));
        return -1;
    }


    timeit(&tp, TP_OPEN_S);
    if ((srcfd = open_file(srcfile, 0, true)) < 0) {
        return -1;
    }

    if ((dstfd = open_file(dstfile, src_size, false)) < 0) {
       return -1;
    }

    timeit(&tp, TP_OPEN_E);
    printf ("Src file %d, Dst file %d\n", srcfd, dstfd);

    timeit(&tp, TP_COPY_S);
    if (copy_file(srcfd, dstfd, src_size) < 0) {
        return -1;
    }
    timeit(&tp, TP_COPY_E);

    close_file(srcfd);
    close_file(dstfd);

    timeprofile_display(&tp);

    return 0;
}
