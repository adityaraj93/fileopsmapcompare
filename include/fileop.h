#ifndef __FILEOP_H__
#define __FILEOP_H__

int fileop_open(const char *filename, long size, bool src);
int fileop_copy(int srcfd, int dstfd, long size);
int fileop_close(int fd);

#endif /* __FILEOP_H__ */
