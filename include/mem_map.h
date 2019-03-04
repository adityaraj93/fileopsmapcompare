#ifndef _MEM_MAP_H_
#define _MEM_MAP_H_

int map_open(const char *filename, long size, bool is_src);
int map_copy(int srcfd, int dstfd, long size);
int map_close(int fd);

#endif /* _MEM_MAP_H_ */
