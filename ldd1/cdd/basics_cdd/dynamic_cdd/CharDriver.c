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

#include <linux/init.h>//Required header for the Intialization and Cleanup Functionalities....
#include <linux/module.h>//This Header contains the necessary stuff for the Module
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/uaccess.h> /* copy_from/to_user */
#include <linux/kdev_t.h> /* MAJOR(dev) macro */
#include <linux/cdev.h>
#define NAME MyCharDevice


//Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *indoe, struct file *filp);
ssize_t NAME_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);


//Structure that defines the operations that the driver provides
struct file_operations fops = 
{
	.owner   = THIS_MODULE,
	.open    = NAME_open, 
	.read    = NAME_read,
	.write   = NAME_write,
	.release = NAME_release,
};

//Structure for a character driver
struct cdev *my_cdev;

dev_t Mydev;

//Init Module
static int __init CharDevice_init(void)
{
	int result;
	int MAJOR,MINOR;

/*	Mydev = MKDEV(255,0);//Create a device number
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\nThe Major Number is %d...THe Minor Number is %d\n",MAJOR,MINOR);
	result=register_chrdev_region(Mydev,1,"MyCharDevice");//register device region.....
	if(result<0)
	{
		printk(KERN_ALERT "\nThe Region requested for is not obtainable\n");
		return(-1);
	}*/
	
	result = alloc_chrdev_region(&Mydev , 0 , 1 , "MyCharDevice");
	if(result<0)
	{
		printk(KERN_ALERT "\nThe Region requested for is not obtainable\n");
		return(-1);
	}
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\nThe Major Number is %d...THe Minor Number is %d\n",MAJOR,MINOR);
	
	
	
	my_cdev = cdev_alloc();//allocate memory to Char Device structure
	my_cdev->ops = &fops;//link our file operations to the char device

	result=cdev_add(my_cdev,Mydev,1);//Notify the kernel abt the new device
	if(result<0)
	{
		printk(KERN_ALERT "\nThe Char Devide has not been created......\n");
		return (-1);
	}
	return 0;
}


//Cleanup Module
void __exit CharDevice_exit(void)
{
/*	dev_t Mydev;
	int MAJOR,MINOR;
	Mydev=MKDEV(255,0);
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\nThe Major Number is %d...THe Minor Number is %d\n",MAJOR,MINOR);*/
	unregister_chrdev_region(Mydev,1);//unregister the device numbers and the device created
	cdev_del(my_cdev);
	printk(KERN_ALERT "\nI have unregistered the stuff that was allocated.....Goodbye for ever.....\n");
	return;
}


//Open System Call
int NAME_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "\nThis is the Kernel....Open Call\n");
	return 0;
}

//Close System Call
int NAME_release(struct inode *indoe, struct file *filp)
{
	printk(KERN_ALERT "\nThis is the release method of my Character Driver\n");
	return 0;
} 


//Write Functionality
ssize_t NAME_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
	char Kbuff[120];
	int result;
	ssize_t retval;
		
	result=copy_from_user((char *)Kbuff , (char *)Ubuff , count);
	if(result == 0)
	{
		printk(KERN_ALERT "\nMessage from the user......\n %s\n",Kbuff);
                printk(KERN_ALERT "\n %d bytes of data Successfully Written.....\n",count);
                retval=count;
                return retval;
		
	}
	else
	{
		printk(KERN_ALERT "\n Error Writing Data\n");
                retval=-EFAULT;
                return retval;

	}
}


//read Functionality	
ssize_t NAME_read(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
	char Kbuff[]="Iam sending from Kernel buffer";
	int result;
	ssize_t retval;

	result=copy_to_user((char *)Ubuff,(const char *)Kbuff,sizeof(Kbuff));
	if(result == 0)
	{
		printk(KERN_INFO"copy to user space is successfully written%d\n",sizeof(Kbuff));
		retval = sizeof(Kbuff);
		//return retval;
		return 0;
		
	}	
	else
        {
                printk(KERN_ALERT"\n Error Writing Data to User\n");
                retval=-EFAULT;
                return retval;
        }

	
}


	
//Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);
