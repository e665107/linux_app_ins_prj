/*
 * a simple kernel module: hr-timer
 *
 * Licensed under GPLv2 or later.
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>

#define MS_TO_NS(x) (x * 1E6L)

static struct hrtimer hr_timer;
static int hr_timer_isr_count = 0;

enum hrtimer_restart my_hrtimer_callback( struct hrtimer *timer )
{
        pr_info( "my_hrtimer_callback called (%ld).\n", jiffies );
        hr_timer_isr_count++;
        if(hr_timer_isr_count < 5)
        {
                hrtimer_restart(&hr_timer);
                return HRTIMER_RESTART;
        }
        return HRTIMER_NORESTART;
}


static int __init hr_timer_init(void)
{
        ktime_t ktime;
        unsigned long delay_in_ms = 200L;

        pr_info("HR Timer module installing\n");
        /*
         * ktime = ktime_set(0, 200 * 1000 * 1000);
         * 200 ms = 10 * 1000 * 1000 ns
         */
        ktime = ktime_set( 0, MS_TO_NS(delay_in_ms) );

        hrtimer_init( &hr_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL );
        hr_timer.function = &my_hrtimer_callback;
        pr_info( "Starting timer to fire in %ldms (%ld)\n", \
                 delay_in_ms, jiffies );

        hrtimer_start( &hr_timer, ktime, HRTIMER_MODE_REL );
        return 0;
}


static void __exit hr_timer_exit(void)
{
        int ret;
        ret = hrtimer_cancel( &hr_timer );
        if (ret)
                pr_info("The timer was still in use...\n");
        hr_timer_isr_count = 0;
        pr_info("HR Timer module uninstalling\n");
        return;
}

module_init(hr_timer_init);
module_exit(hr_timer_exit);

MODULE_AUTHOR("e665106");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A simple hr-timer Module");
MODULE_ALIAS("a simplest module"); 




 
