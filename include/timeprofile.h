#ifndef __TIMEPROFILE_H__
#define __TIMEPROFILE_H__

#include <sys/time.h>

struct timeprofile
{
    time_t op_start;
    time_t op_open;
    time_t op_read;
    time_t op_write;
};
typedef struct timeprofile timeprofile_t;
#define timeprofile_s sizeof(struct timeprofile)


#endif /* __TIMEPROFILE_H__ */
