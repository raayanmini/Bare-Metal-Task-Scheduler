#ifndef SYSTICK_TIMER_H
#define SYSTICK_TIMER_H

/*
 * systick_timer.h
 *
 * Created on: Nov 15, 2024
 * Author: Hitesh Behera
 */

#include <stdint.h>

typedef uint32_t tick_t;

#define TICK_T_MAX      UINT32_MAX
#define MDELAY          1U
#define UDELAY          0U

/**
 * Busy-wait for the requested number of milliseconds.
 * Do not call this function from a cooperative scheduled task.
 */
void KM_mdelay(uint32_t ms);

/** Configure SysTick as the scheduler's millisecond time base. */
void systickInit(void);

#endif /* SYSTICK_TIMER_H */
