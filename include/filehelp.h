#ifndef FILEHELP_H
#define FILEHELP_H

#include <stdbool.h>

bool file_exists(const char *filename);
long file_size(const char *filename);
long file_size_fd(int fd);

#endif /* FILEHELP_H */
