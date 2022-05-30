/*
 * a simple kernel module: k-thread
 *
 * Licensed under GPLv2 or later.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/rwlock.h>
#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/delay.h>

struct task_struct *my_task;
static int k_thread_cycle_count = 0;
static int mykthread(void *unused)
{
        
        for (;;) {
                pr_info("mykthread is living!, count: %d\n", k_thread_cycle_count);
                ssleep(10);
                k_thread_cycle_count++;
                if(k_thread_cycle_count > 5)
                        kthread_stop(my_task);
        }
        return 0;
}


static int __init k_thread_init(void)
{

        my_task = kthread_run(mykthread, NULL,
                              "mykthread");
	if (my_task == ERR_PTR(-ENOMEM)) {
		printk(KERN_INFO " mykthread creation failed\n");
		my_task = NULL;
		return -ENOMEM;
	}

        return 0;
}

module_init(k_thread_init);

static void __exit k_thread_exit(void)
{
        kthread_stop(my_task);
        printk(KERN_INFO "k_thread exit\n ");
}


module_exit(k_thread_exit);

MODULE_AUTHOR("e665106");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("A simple k-thread Module");
MODULE_ALIAS("a simplest module"); 




