#include "scheduler.h"
#include "tasks.h"
#include "systick_timer.h"

/* Updated by SysTick_Handler() once every millisecond. */
extern volatile tick_t jiffy;

/*
 * Static task table.
 *
 * Each entry contains:
 *   1. task function
 *   2. execution period in milliseconds
 *   3. timestamp of the previous dispatch
 *
 * A task can update its own period before returning. This defers its next call
 * without blocking the dispatcher. Because the next call starts again at the
 * task function's first statement, multi-step task logic must preserve its
 * progress explicitly in static, global, or task-control-block state.
 */
tcb_t taskList[MAX_TASKS] =
{
    { task1_redLedBlink,   1000U, 0U },
    /* Task 2 changes this initial 250 ms value to 1000 ms at startup. */
    { task2_greenLedBlink,  250U, 0U }
};

void startScheduler(void)
{
    uint8_t i;
    tick_t now;

    /*
     * Run every task once during scheduler startup so the demonstration
     * produces an immediate visible result. Record a common start time for
     * the next periodic dispatch.
     */
    now = jiffy;
    for (i = 0U; i < MAX_TASKS; i++)
    {
        taskList[i].lastRunTime = now;
        taskList[i].task();
    }

    /*
     * Cooperative dispatcher: tasks run one at a time and must return. The
     * scheduler calls a due task from its entry point; it does not resume a
     * saved instruction position as an RTOS context switch would.
     */
    while (1)
    {
        for (i = 0U; i < MAX_TASKS; i++)
        {
            /* Read the volatile tick counter for the current task check. */
            now = jiffy;

            /*
             * Unsigned subtraction keeps this comparison valid when the
             * 32-bit tick counter wraps around.
             *
             * A zero period is treated as disabled to avoid continuously
             * dispatching a task because of an invalid configuration.
             */
            if ((taskList[i].period != 0U) &&
                ((tick_t)(now - taskList[i].lastRunTime) >=
                 taskList[i].period))
            {
                /* Schedule the next interval from this dispatch time. */
                taskList[i].lastRunTime = now;

                /* Call the task through its function pointer. */
                taskList[i].task();
            }
        }
    }
}
