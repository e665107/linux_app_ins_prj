
#ifndef __SW_TIMER_H__
#define __SW_TIMER_H__

#define HZ         1000000

#define NS_PER_SEC 1000000000
#define US_PER_SEC 1000000
#define MS_PER_SEC 1000

/* Convert cycle to seconds and vice versa */
#define CYCLE2SEC(cycle) ((cycle) / HZ)
#define SEC2CYCLE(sec)   ((uint64_t) (sec) * HZ)

/* Convert cycle to milliseconds and vice versa */
#define CYCLE2MS(msec) ((msec) / (HZ / MS_PER_SEC))

/* Convert cycle to microseconds and vice versa */
#define CYCLE2US(msec) ((msec) / (HZ / US_PER_SEC))

/* Convert cycle to nanoseconds and vice versa */

/* Difference between two 'rdtime' values in cycle */
#define RDTIME_DIFF(a, b) ((a) - (b))

/*******************************************************************************
 * GETTIME
 *   Wrapper over various *gettime* functions
 ******************************************************************************/
#define GETTIME(tsp)                                                           \
    do {                                                                       \
        __asm__ __volatile__("rdtime %0" : "=r"(tsp));                         \
    } while (0)

/*******************************************************************************
 * Timer structure definition
 ******************************************************************************/
typedef struct
{
    uint64_t time_start;
    uint64_t time_end;
    uint64_t events;
    uint64_t queue_time;
    uint64_t min_time;
    uint64_t max_time;
    uint64_t sum_time;
} sw_timer_t;

/*******************************************************************************
 * SW_Timer_Start
 *   start timer
 ******************************************************************************/
__STATIC_FORCEINLINE
void SW_Timer_Start(sw_timer_t *t)
{
    GETTIME(t->time_start);
    return;
}

/*******************************************************************************
 * SW_Timer_Stop
 *   stop timer
 ******************************************************************************/
__STATIC_FORCEINLINE
uint64_t SW_Timer_Stop(sw_timer_t *t)
{
    uint64_t elapsed = 0;

    GETTIME(t->time_end);

    elapsed = RDTIME_DIFF(t->time_end, t->time_start) + t->queue_time;

    t->events++;
    t->sum_time += elapsed;

    if (__rv_unlikely(elapsed < t->min_time))
        t->min_time = elapsed;
    if (__rv_unlikely(elapsed > t->max_time))
        t->max_time = elapsed;

    return elapsed;
}

/*******************************************************************************
 * SW_Timer_Reset
 *   Reset timer counters, but leave the current state intact
 ******************************************************************************/
__STATIC_FORCEINLINE
void SW_Timer_Reset(sw_timer_t *t)
{
    t->min_time   = __UINT64_MAX__;
    t->max_time   = 0;
    t->sum_time   = 0;
    t->events     = 0;
    t->queue_time = 0;
    return;
}

/*******************************************************************************
 * SW_Timer_Init
 *   initialize timer
 ******************************************************************************/
__STATIC_FORCEINLINE
void SW_Timer_Init(sw_timer_t *t)
{
    SW_Timer_Reset(t);
}

/*******************************************************************************
 * SW_Timer_Events
 *   get total events
 ******************************************************************************/
__STATIC_FORCEINLINE
uint64_t SW_Timer_Events(sw_timer_t *t)
{
    return t->events;
}

/*******************************************************************************
 * SW_Timer_Avg
 *   get average time per event
 ******************************************************************************/
__STATIC_FORCEINLINE
uint64_t SW_Timer_Avg(sw_timer_t *t)
{
    if (t->events == 0)
        return 0; /* return zero if there were no events */
    return (t->sum_time / t->events);
}

/*******************************************************************************
 * SW_Timer_Sum
 *   get total time for all events
 ******************************************************************************/
__STATIC_FORCEINLINE
uint64_t SW_Timer_Sum(sw_timer_t *t)
{
    return t->sum_time;
}

/*******************************************************************************
 * SW_Timer_Min
 *   get minimum time
 ******************************************************************************/
__STATIC_FORCEINLINE
uint64_t SW_Timer_Min(sw_timer_t *t)
{
    if (t->events == 0)
        return 0;
    return t->min_time;
}

/*******************************************************************************
 * SW_Timer_Max
 *   get maximum time
 ******************************************************************************/
__STATIC_FORCEINLINE
uint64_t SW_Timer_Max(sw_timer_t *t)
{
    return t->max_time;
}

#endif

