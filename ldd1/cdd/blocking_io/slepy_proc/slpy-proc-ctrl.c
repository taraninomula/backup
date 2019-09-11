/*
 * slpy-proc-ctrl.c 
 *
 * Simple demo driver; readers are put to sleep on a 
 * wait queue. Any writer coming along awakens the readers.
 *
 * In addition, this driver incorporates a proc entry letting the user
 * control the behaviour.
 * Writing into the proc entry will have this effect:
 *    If ASCII "0" is written to this (virtual) file, the value of
 *    the global variable "wake_one" is reset to zero.
 *    If ASCII "1" is written to this (virtual) file, "wake_one" is 
 *    set to one.
 *    If ASCII "2" is written to this (virtual) file, "data_present" is 
 *    reset to zero.
 * Reading from the proc entry will display the current values of
 * both the "wake_one" and "data_present" variables.
 *
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

#define	DEBUG		1   /* set to 0 to turn off debug messages */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/wait.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>	/* current, jiffies */
#include <asm/uaccess.h>

#define	DRVNAME		"slpy"

#ifdef DEBUG
	#define MSG(string, args...) \
		printk(KERN_DEBUG "%s:%s:%d: " string, \
			DRVNAME, __FUNCTION__, __LINE__, ##args)
#else
	#define MSG(string, args...)
#endif

/* In a "real" driver, we would require the use of concurrency control
 * mechansims, which we just ignore in this simple demo case.
 */
static int sleepy_major=0, 
	   data_present=0, 	/* event condition flag */
	   wake_one=0;		/* parameter- see below */
DECLARE_WAIT_QUEUE_HEAD(wq);

/*------------------------ Module stuff */
module_param (wake_one, int, 0); /* 0 => param won't show up in sysfs, 
					non-zero are mode (perms) */
MODULE_PARM_DESC (wake_one,
"Set to 1 to enable wake up of only one task on \
a blocking read (default is 0).");

MODULE_DESCRIPTION("Demo of using a wait queue.");
MODULE_LICENSE("GPL");


static ssize_t sleepy_read(struct file *filp, char __user *buf, 
			size_t count, loff_t *offp)
{
	if (!data_present)
		MSG("process %d (%s) going to sleep\n", 
				current->pid, current->comm);

	if (wait_event_interruptible(wq, (data_present==1))) {
		MSG("wait interrupted by signal, ret -ERESTARTSYS to VFS..\n");
		return -ERESTARTSYS;
	}
	/* 
	 * Blocks here..the reader (user context) process is put to sleep
	 * this is actually effected by making the 
	 * task state <- TASK_INTERRUPTIBLE and invoking the scheduler.
	 *
	 * If we set the event condition flag (data_present) to false now, 
	 * _all_ tasks 
	 * will be awoken on the driver's wake_up* call, but only _one_ of 
	 * them will actually perform the (hardware) read; the others will 
	 * automatically go to sleep again because of the semantics of 
	 * the code. (One task will set data_present to false, causing the 
	 * others to go to sleep again. The discerning reader will notice
	 * that there is a possible race here- we show how to take care of 
	 * that in the next section).
	 *
	 * If you prefer to have all tasks awaken _and_ read the data, then
	 * don't set the condition to false now. 
	 *
	 * Hence it's fully in the control of the driver author. We simulate 
	 * this by having a module parameter "wake_one". It is zero (off) by
	 * default but can be set to one (on) to simulate the above case.
	 */
	if (wake_one)
		data_present = 0; /* event flag set to the False state */

	MSG("awoken %d (%s), data_present=%d\n", 
			current->pid, current->comm, data_present);
	return 0; /* EOF */
}

static ssize_t sleepy_write(struct file *filp, const char __user *buf, 
			size_t count, loff_t *offp)
{
	MSG("process %d (%s) awakening the sleeping readers, if any...\n",
		current->pid, current->comm );

	data_present = 1;
	wake_up_interruptible(&wq); 
		/* Awakens all interruptible sleepers on wq */

	return count; /* succeed, to avoid retrial */
}


/*----------------------- Proc entry functionality --------------------*/
#define MAXLEN 1

/* 
 * write callback:
 * If ASCII "0" is written to this (virtual) file, the value of
 * the global variable "wake_one" is reset to zero.
 * If ASCII "1" is written to this (virtual) file, "wake_one" is 
 * set to one.
 * If ASCII "2" is written to this (virtual) file, "data_present" is 
 * reset to zero.
 *
 * Note: The read/update of global(s) _requires_ concurrency control - 
 * locking. Here, we ignore this issue.
 */
static ssize_t write_wake_one(struct file *filp, const char __user * buffer, 
		size_t count, loff_t *offp)
{
	char kbuf[MAXLEN+1];
	int mycount = count;
	
	if (count > MAXLEN) {
		printk(KERN_INFO 
			"%s: write_wake_one expects %d characters max, \
limit exceeded. Aborting write...\n", DRVNAME, MAXLEN);
		return -EINVAL;
	}

	MSG("1. data_present=%d wake_one=%d\n", data_present, wake_one);
	
	if (copy_from_user (kbuf, buffer, mycount)) {
		MSG("copy_from_user failed\n");
		return -EFAULT;
	}
	kbuf[mycount] = '\0';
	/*MSG("kbuf : %s (0x%x)\n", kbuf, kbuf[0]);*/

	switch (kbuf[0]) {
		case 0x30 : 		/* ASCII "0" written */
			wake_one = 0;
			break;
		case 0x31 : 		/* ASCII "1" written */
			wake_one = 1;
			break;
		case 0x32 : 		/* ASCII "2" written */
			data_present = 0;
			break;
		default :
			printk(KERN_INFO 
			"%s: write_wake_one expects either an ASCII \"0\", \
\"1\" or \"2\" to be written in. Invalid value \"%s\" written, \
aborting write..\n", 
			DRVNAME, kbuf);
			return -EINVAL;
	}
	
	MSG("2. data_present=%d wake_one=%d\n", data_present, wake_one);
	return mycount;
}

/* read callback
 * Note: The read/update of global(s) _requires_ concurrency control - 
 * locking. Here, we ignore this issue.
 */
static ssize_t read_stat(struct file *filp, char __user *buf, 
			size_t count, loff_t *offp)
//static int read_stat(char __user *buf, char **start, off_t offset,
  //                 int count, int *eof, void *data)
{
char memory_buffer[30];

sprintf (memory_buffer, "data_present=%d wake_one=%d\n", 
			data_present, wake_one);
copy_to_user(buf,memory_buffer,27);
if ( *offp == 0)
{
*offp++;
return 27;
}
else
{
return 0;
}

}

/*-------------------------------------------------------------------*/


static struct file_operations sleepy_fops = {
//	.owner = 	THIS_MODULE,
	.llseek = 	no_llseek,
	.read = 	sleepy_read,
	.write = 	sleepy_write,
};


static const struct file_operations proc_fops = {
//	.owner  =  	THIS_MODULE,
	.read   = 	read_stat,
	.write  = 	write_wake_one,
};
static int __init slpy_init_module(void)
{
	int result;
	struct proc_dir_entry *res;
	char procname[272];

	result = register_chrdev(sleepy_major, DRVNAME, &sleepy_fops);
	if (result < 0) 
		return result;

	if (sleepy_major == 0)
		sleepy_major = result;
	printk(KERN_DEBUG "sleepy: major # = %d\n", sleepy_major);

	/* Setup a RW proc entry for controlling the value of "wake_one"
	 * at runtime.
	 */
	snprintf (procname, 272, "driver/%s.wake_one", DRVNAME); /* 16+256 */
	if (!(res = proc_create (procname, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP, NULL, &proc_fops))) {
		MSG("%s proc entry creation failure, aborting..\n", procname);
		unregister_chrdev(sleepy_major, DRVNAME);
		return -ENOMEM;
	}
//	res->owner = THIS_MODULE;
//	res->read_proc = read_stat;
//	res->write_proc = write_wake_one;
//	res->data = NULL;
	
	printk(KERN_INFO "%s: Loaded ok. wake_one is %s now. \
Proc entry \"%s\" created.\n", 
			DRVNAME, wake_one ? "ON" : "OFF", procname);
	return 0; /* success */
}

static void __exit slpy_cleanup_module(void)
{
	char procname[272];

	snprintf (procname, 272, "driver/%s.wake_one", DRVNAME); /* 16+256 */
	remove_proc_entry (procname, NULL);

	unregister_chrdev(sleepy_major, DRVNAME);
	printk(KERN_INFO "%s removed.\n", DRVNAME);
}

module_init(slpy_init_module);
module_exit(slpy_cleanup_module);
