/*
 * a simple kernel module: shared-workqueue
 *
 * Licensed under GPLv2 or later.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>    /* for sleep */
#include <linux/wait.h>     /* for wait queue */
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/slab.h>         /* for kmalloc() */
#include <linux/workqueue.h>

static int sleep = 0;

struct work_data {
        struct work_struct my_work;
        wait_queue_head_t my_wq;
        int the_data;
};

static void work_handler(struct work_struct *work)
{
        struct work_data *my_data = container_of(work, \
                                                 struct work_data, my_work); 
        pr_info("Work queue module handler: %s, data is %d\n", __FUNCTION__, my_data->the_data);
        msleep(30);
        wake_up_interruptible(&my_data->my_wq);
        kfree(my_data);
}

static int __init shared_workqueue_init(void)
{
        struct work_data * my_data;

        my_data = kmalloc(sizeof(struct work_data), GFP_KERNEL);
        my_data->the_data = 34;

        INIT_WORK(&my_data->my_work, work_handler);
        init_waitqueue_head(&my_data->my_wq);

        schedule_work(&my_data->my_work);
        pr_info("I'm goint to sleep ...\n");
        wait_event_interruptible(my_data->my_wq, sleep != 0);
        pr_info("I am Waked up...\n");
        return 0;
}

module_init(shared_workqueue_init);

static void __exit shared_workqueue_exit(void)
{
        printk(KERN_INFO "shared_workqueue exit\n ");
}


module_exit(shared_workqueue_exit);

MODULE_AUTHOR("e665106");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A simple shared-workqueue Module");
MODULE_ALIAS("a simplest module"); 




 
