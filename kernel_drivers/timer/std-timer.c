/*
 * a simple kernel module: std-timer
 *
 * Licensed under GPLv2 or later.
 */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/version.h>

/* 1 jiffy---10ms */
static struct timer_list my_timer;

static int timer_isr_enter_counts = 0;

#if (KERNEL_VERSION(4, 19, 0) > LINUX_VERSION_CODE)
void my_timer_callback( unsigned long data )
{
        int retval;
        pr_info( "%s called (%ld).\n", __FUNCTION__, jiffies );
        timer_isr_enter_counts++;
        if(timer_isr_enter_counts < 5){
                
                retval = mod_timer( &my_timer, jiffies + msecs_to_jiffies(1000) );
                if (retval)
                        pr_info("Timer firing failed\n");
        }
}
#else
void my_timer_callback(struct timer_list *timer)
{
        int retval;
        pr_info( "%s called (%ld).\n", __FUNCTION__, jiffies );
        timer_isr_enter_counts++;
        if(timer_isr_enter_counts < 5){
                
                retval = mod_timer(timer, jiffies + msecs_to_jiffies(1000) );
                if (retval)
                        pr_info("Timer firing failed\n");
        }
}
#endif

static int __init timer_init(void)
{
        int retval;
        pr_info("Timer module loaded\n");

#if (KERNEL_VERSION(4, 19, 0) > LINUX_VERSION_CODE)
        setup_timer( &my_timer, my_timer_callback, 0 );
#else
        timer_setup(&my_timer, my_timer_callback, 0);
#endif
        pr_info( "Setup timer to fire in 300ms (%ld)\n", jiffies );

        retval = mod_timer( &my_timer, jiffies + msecs_to_jiffies(300) );
        if (retval)
                pr_info("Timer firing failed\n");
 
        return 0;
}

static void __exit timer_exit(void)
{
    int retval;
    retval = del_timer( &my_timer );
    if (retval)
        pr_info("The timer is still in use...\n");
    timer_isr_enter_counts = 0;
    pr_info("Timer module unloaded\n");
    return;
}

module_init(timer_init);
module_exit(timer_exit);

MODULE_AUTHOR("e665106");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A simple timer Module");
MODULE_ALIAS("a simplest module"); 




