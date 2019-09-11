/*
 * slpy_wq.c
 *
 * Simple demo driver; readers are put to sleep on a 
 * wait queue. Any writer coming along awakens the readers.
 *
 * Additionally, in order to demo a Work Queue feature, we have a work queue
 * structure set up: when the driver's write method is invoked, it schedules 
 * the 'deferred work' function of our work queue. This function, in order to 
 * do something, starts up and constantly resets a kernel timer.
 *
 * This version does NOT correctly implement SMP locking, for simplicity (left 
 * as an exercise to the participant!); this is done in the slpy_proper.c driver.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


/* 
 * #define	DEBUG	1     //set to 0 to turn off debug messages
 * 
 * Lets not hardcode the debug flag. In the Makefile, 
 * you can specify this using:
 * EXTRA_CFLAGS += -DDEBUG
 * (under the "obj-m" line) if you want the flag defined.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/wait.h>
#include <linux/fs.h>
#include <linux/sched.h>	/* current, jiffies */
#include "convenient.h"

#define	DRVNAME		"slpy_wq"

/* In a "real" driver, we would require the use of concurrency control
 * mechanisms, which we just ignore in this simple demo case.
 */
static int sleepy_major=0, 
	   data_present=0; 	/* event condition flag */
DECLARE_WAIT_QUEUE_HEAD(wq);

static struct work_struct ws;
static struct timer_list timr;
static int count, delaysec=7;


/*------------------------ Module stuff */
MODULE_AUTHOR("Kernel Masters");
MODULE_DESCRIPTION("Demo of using a work queue (and timer).");
MODULE_LICENSE("GPL");

/* This is the timeout function. */
static void whee(unsigned long data)
{
	MSG("Timed out. count=%d jiffies=%ld\n", count, jiffies);
#if 1
	//dump_stack();
#endif

	/* Reset and activate the timer */
	timr.expires = jiffies + delaysec*HZ;
	timr.data = ++count;
	timr.function = whee;
	add_timer (&timr);
}

/* This is our deferred processing work queue handler. */
static void wq_func(void)
{
	MSG ("We're here doing some deferred work! HZ=%d jiffies=%ld\n", HZ, jiffies);
	MSG ("Now setting up a timer...\n");

	/* Setup and activate the timer */
	timr.expires = jiffies + delaysec*HZ;
	timr.data = ++count;
	timr.function = whee;
	add_timer (&timr);
}


static ssize_t sleepy_read(struct file *filp, char __user *buf, 
			size_t count, loff_t *offp)
{
	MSG("process %d (%s) going to sleep\n", current->pid, current->comm);//current->comm if for binary program name

	if (wait_event_interruptible(wq, (data_present==1))) {
		MSG("wait interrupted by signal, ret -ERESTARTSYS to VFS..\n");
		return -ERESTARTSYS;
	}

	MSG("awoken %d (%s), data_present=%d\n", 
			current->pid, current->comm, data_present);

	return 0; /* EOF */
}

static ssize_t sleepy_write(struct file *filp, const char __user *buf, 
			size_t count, loff_t *offp)
{
	MSG("Scheduling deferred work in the work queue now...\n");
	schedule_work (&ws);

	MSG("process %d (%s) awakening the readers...\n",
		current->pid, current->comm );

	data_present = 1;
	wake_up_interruptible(&wq); 
		/* Awakens all interruptible sleepers on wq */

	return count; /* succeed, to avoid retrial */
}


static struct file_operations sleepy_fops = {
	.owner = 	THIS_MODULE,
	.llseek = 	no_llseek,
	.read = 	sleepy_read,
	.write = 	sleepy_write,
};

static int __init slpy_init_module(void)
{
	int result;

	result = register_chrdev(sleepy_major, DRVNAME, &sleepy_fops);
	if (result < 0) 
		return result;

	if (sleepy_major == 0)
		sleepy_major = result;
	printk(KERN_DEBUG "sleepy: major # = %d\n", sleepy_major);

	INIT_WORK(&ws, wq_func);
	init_timer (&timr);

	MSG("Loaded ok.\n");
	return 0; /* success */
}

static void __exit slpy_cleanup_module(void)
{
	del_timer_sync (&timr);
	flush_scheduled_work ();
	unregister_chrdev(sleepy_major, DRVNAME);
	MSG("Removed.\n");
}

module_init(slpy_init_module);
module_exit(slpy_cleanup_module);

