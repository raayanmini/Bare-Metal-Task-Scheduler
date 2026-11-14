#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "systick_timer.h"

#define MAX_TASKS       2U

typedef void (*taskPtr)(void);

typedef struct
{
    taskPtr task;          /* Task entry function. */
    tick_t period;         /* Interval between task dispatches, in ms. */
    tick_t lastRunTime;    /* Tick value recorded at the previous dispatch. */
} tcb_t;

/* Static task table defined in scheduler.c. */
extern tcb_t taskList[MAX_TASKS];

void startScheduler(void);

#endif /* SCHEDULER_H */
