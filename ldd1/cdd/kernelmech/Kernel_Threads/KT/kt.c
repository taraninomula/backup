/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page   : www.facebook.com/kernelmasters                   *
 *                                                                         *
 *  Conducting Workshops on - Embedded Linux & Device Drivers Training.    *
 *  -------------------------------------------------------------------    *
 *  Tel : 91-9949062828, Email : kernelmasters@gmail.com                   *
 *                                                                         *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation. No warranty is attached; we cannot take *
 *   responsibility for errors or fitness for use.                         *
 ***************************************************************************/

#include <linux/module.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#define seconds_to_jiffies(sec) (cputime_to_jiffies(secs_to_cputime(sec)))

static struct task_struct *sender_thread = NULL;

static int my_sender_thread (void *data)
{
	printk ("name: %s PID: %d TGID: %d\n", current->comm, current->pid, current->tgid);
	while(1)
	{
		printk("Hi I am kernel thread!\n");
		//mdelay(100);
		set_current_state (TASK_INTERRUPTIBLE);
		schedule_timeout(seconds_to_jiffies(3));
		schedule();
		if (kthread_should_stop())
		break;
	}
    	return 0;

}             

static int __init my_init (void)
{
    sender_thread = kthread_run (my_sender_thread, NULL, "kernel_thread");
    if (IS_ERR (sender_thread)) {
        printk ("Error %ld creating thread\n",
                PTR_ERR (sender_thread));
        return -1;
    }
    printk ("Starting Kernel thread in init module\n");

    return 0;
}

static void __exit my_exit (void)
{
	printk (KERN_INFO "Exiting kernel_thread module\n");
	kthread_stop(sender_thread);
}

module_exit (my_exit);
module_init (my_init);

MODULE_AUTHOR ("Kernel Masters");
MODULE_DESCRIPTION ("JOC: Android for Embedded Systems, KPHB, Hyderabad");
MODULE_LICENSE ("GPL v2");
