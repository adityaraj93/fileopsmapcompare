#ifndef __TIMEPROFILE_H__
#define __TIMEPROFILE_H__

#include <time.h>

enum timeprof_event {
    TP_START = 1,
    TP_OPEN_S,
    TP_OPEN_E,
    TP_COPY_S,
    TP_COPY_E
};

struct timeprofile {
    struct timespec op_start;
    struct timespec op_open[2]; // [0] start, [1] end
    struct timespec op_copy[2]; // [0] start, [1] end
};
typedef struct timeprofile timeprofile_t;

void timeit(timeprofile_t *tp, enum timeprof_event event);
void timeprofile_display(timeprofile_t *tp);

#endif /* __TIMEPROFILE_H__ */
