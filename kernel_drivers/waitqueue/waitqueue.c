/*
 * a simple kernel module: waitqueue
 *
 * Licensed under GPLv2 or later.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/time.h>
#include <linux/delay.h>
#include<linux/workqueue.h>


static DECLARE_WAIT_QUEUE_HEAD(my_wq);
static int condition = 0;

/* declare a work queue*/
static struct work_struct wrk;

static void work_handler(struct work_struct *work)
{ 
        pr_info("Waitqueue module handler %s\n", __FUNCTION__);
        msleep(3000);
        pr_info("Wake up the sleeping module\n");
        condition = 1;
        wake_up_interruptible(&my_wq);
}


static int __init waitqueue_init(void)
{
        
        pr_info("Wait queue example\n");

        INIT_WORK(&wrk, work_handler);
        schedule_work(&wrk);  /* put work task in global workqueue */

        pr_info("Going to sleep %s\n", __FUNCTION__);
        wait_event_interruptible(my_wq, condition != 0);  /*wake_up_interruptible(&my_wq); && condition = 1;, program will go on  */

        pr_info("woken up by the work job\n");
        return 0;
}

module_init(waitqueue_init);

static void __exit waitqueue_exit(void)
{
        printk(KERN_INFO "waitqueue exit\n ");
}


module_exit(waitqueue_exit);

MODULE_AUTHOR("e665106");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A simple waitqueue Module");
MODULE_ALIAS("a simplest module"); 




 
