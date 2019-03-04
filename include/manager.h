#ifndef MANAGER_H
#define MANAGER_H

enum op_mode {
    OP_MD_FILEOP = 1,
    OP_MD_MMAP
};

int manage(enum op_mode opmode, const char *srcfile, const char *dstfile);

#endif /* MANAGER_H */
