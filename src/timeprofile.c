#include <stdio.h>
#include <time.h>

#include "timeprofile.h"

void timeit(timeprofile_t *tp, enum timeprof_event event) {
    struct timespec *tsp = NULL;
    switch (event)
    {
        case TP_START:
            tsp = &(tp->op_start);
            break;
        case TP_OPEN_S:
            tsp = &(tp->op_open[0]);
            break;
        case TP_OPEN_E:
            tsp = &(tp->op_open[1]);
            break;
        case TP_COPY_S:
            tsp = &(tp->op_copy[0]);
            break;
        case TP_COPY_E:
            tsp = &(tp->op_copy[1]);
            break;
    }
    clock_gettime(CLOCK_MONOTONIC, tsp);
}

void timeprofile_display(timeprofile_t *tp) {
    long stime, etime;

    printf("\nProfile:\n");

    printf("Start Time: %lld.%.9ld\n", (long long)(tp->op_start.tv_sec), tp->op_start.tv_nsec);

    printf ("Open Start time: %lld.%.9ld\n", (long long)(tp->op_open[0].tv_sec), tp->op_open[0].tv_nsec);
    printf ("Open End   time: %lld.%.9ld\n", (long long)(tp->op_open[1].tv_sec), tp->op_open[1].tv_nsec);
    printf ("Open Time      : %lld.%.9ld\n", (long long)((tp->op_open[1].tv_sec) - (tp->op_open[0].tv_sec)),
                                            (tp->op_open[1].tv_nsec - tp->op_open[0].tv_nsec));


    stime = (tp->op_copy[0].tv_sec * 1000000000) + tp->op_copy[0].tv_nsec;
    etime = (tp->op_copy[1].tv_sec * 1000000000) + tp->op_copy[1].tv_nsec;
    printf ("\n\nCopy Start time: %lld.%.9ld\n", (long long)(tp->op_copy[0].tv_sec), tp->op_copy[0].tv_nsec);
    printf ("Copy End   time: %lld.%.9ld\n", (long long)(tp->op_copy[1].tv_sec), tp->op_copy[1].tv_nsec);
    printf ("Copy Time      : %.9ld\n", etime - stime);
}
