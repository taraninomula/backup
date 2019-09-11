/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page	: www.facebook.com/kernelmasters                   *
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

#include <linux/kernel.h> /* printk */
#include <linux/module.h>/* This Header contains the necessary stuff for the Module */
#include <linux/init.h> /* Required header for the Intialization and Cleanup Functionalities....  */
#include <linux/fs.h> /* struct file_operations, struct file and struct inode */

#define NAME "Mychar"
#define MAJOR 60

ssize_t my_read(struct file *, char __user *, size_t, loff_t *);
ssize_t my_write(struct file *, const char __user *, size_t, loff_t *);
int my_open(struct inode *, struct file *);
int my_close(struct inode *, struct file *);

struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_close
};


/*Device methods */
ssize_t my_read(struct file *filp, char __user *usr, size_t size, loff_t *off)
{
	printk("Reading from device\n");
	return 0; //-EPERM;
}

ssize_t my_write(struct file *filp, const char __user *usr, size_t size, loff_t *off)
{
	printk("Trying to write into the device\n");
	return size; //-EPERM;
}

int my_open(struct inode *ino, struct file *filp)
{
	printk("device opened\n");
	return 0;
}

int my_close(struct inode *ino, struct file *filp)
{
	printk("device closed\n");
	return 0;
}

int char_init(void)
{
	int result;
        result = register_chrdev(MAJOR, NAME, &fops);
	if(result < 0)
	{
		printk("Device could not be registered\n");
		return -EPERM;
	}
	printk("Driver registered with major %d\n", MAJOR);
	return 0;
}


void char_exit(void)
{
	unregister_chrdev(MAJOR, NAME);
	printk("simple_char unregistered\n");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("GPL");
