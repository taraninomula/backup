/*
 * slpy.c 
 * Simple demo driver; readers are put to sleep on a 
 * wait queue. Any writer coming along awakens the readers.
 * This version does implement proper SMP locking.
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

#define	DRVNAME		"slpy"

#ifdef DEBUG
	#define MSG(string, args...) printk(KERN_DEBUG "%s:%s:%d: " string, \
			DRVNAME, __FUNCTION__, __LINE__, ##args)
#else
	#define MSG(string, args...)
#endif

static atomic_t data_present=ATOMIC_INIT(0); /* event condition flag */
static int sleepy_major=0;
DECLARE_WAIT_QUEUE_HEAD(wq);

MODULE_AUTHOR("Kernel Masters");
MODULE_DESCRIPTION("Trivial demo of using a wait queue.");
MODULE_LICENSE("GPL");


/* 
 * In this demo driver, we just put the current reader to sleep 
 * trivially..; in a 'real' driver one would check: no data available?
 * put the reader to sleep, else continue...stuff like that.
 */
static ssize_t sleepy_read(struct file *filp, char __user *buf, size_t count, loff_t *offp)
{
	if (atomic_read (&data_present) == 0) {
		MSG("process %d (%s) going to sleep\n", current->pid, current->comm);
		if (wait_event_interruptible(wq, (atomic_read (&data_present)==1))) {
	//	if (wait_event(wq, (atomic_read (&data_present)==1))) {
			MSG("wait interrupted by signal, ret -ERESTARTSYS to VFS..\n");
			return -ERESTARTSYS;
		}
		/* 
		 * Blocks here..the reader (user context) process is put to sleep;
	         * this is actually effected by making the 
		 * task state <- TASK_INTERRUPTIBLE and invoking the scheduler.
		 */
		MSG("awoken %d (%s), data_present=%d\n", 
			current->pid, current->comm, atomic_read (&data_present));
	} else {
		MSG ("%d (%s): Data is available, proceeding...\n",
			current->pid, current->comm);
		count=0;
		/* Actual read work done here (in a 'real' driver)...*/
	}
	return count;
}

static ssize_t sleepy_write(struct file *filp, const char __user *buf, 
			size_t count, loff_t *offp)
{
	MSG("process %d (%s) awakening the readers...\n",
		current->pid, current->comm );

	/* Set the wake-up event condition to True, simulating the 
 	 * "data is available" condition... */
	atomic_set (&data_present, 1);
	/* and awaken all the lazy sleepy heads :-) */
	wake_up_interruptible(&wq); 
	//wake_up(&wq); 

	return count;
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

	return 0; /* success */
}

static void __exit slpy_cleanup_module(void)
{
	unregister_chrdev(sleepy_major, DRVNAME);
	MSG("Removed.\n");
}

module_init(slpy_init_module);
module_exit(slpy_cleanup_module);
