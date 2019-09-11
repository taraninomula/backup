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

//Initialization Functions...........
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/semaphore.h>
#define NAME MyCharDevice


//Function Prototypes
int NAME_open(struct inode *inode, struct file *filp);
int NAME_release(struct inode *indoe, struct file *filp);
ssize_t NAME_write_add(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t NAME_read_add(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t NAME_write_sub(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t NAME_read_sub(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t NAME_write_mul(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t NAME_read_mul(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t NAME_write_div(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp);
ssize_t NAME_read_div(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp);


//Structure that defines the operations that the driver provides
struct file_operations fops = 
{
	.owner   = THIS_MODULE,
	.open    = NAME_open, 
	.read    = NAME_read_sub,
	.write   = NAME_write_sub,
	.release = NAME_release,
};

//Structure for a character driver
struct cdev *my_cdev;
int add_result, sub_result, mul_result, div_result;
dev_t Mydev, MyTestdev;

struct semaphore MySem;

//Init Module
static int __init CharDevice_init(void)
{
	int result;
	int MAJOR,MINOR;
/*
	Mydev = MKDEV(255,0);//Create a device number
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\nThe Major Number is %d...THe Minor Number is %d\n",MAJOR,MINOR);
	result=register_chrdev_region(Mydev,1,"MyCharDevice");//register device region.....
	if(result<0)
	{
		printk(KERN_ALERT "\nThe Region requested for is not obtainable\n");
		return(-1);
	}
*/	
	result = alloc_chrdev_region(&Mydev,0,4,"MyCharDevice");
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

	result=cdev_add(my_cdev,Mydev,4);//Notify the kernel abt the new device
	if(result<0)
	{
		printk(KERN_ALERT "\nThe Char Devide has not been created......\n");
		return (-1);
	}
        sema_init (&MySem,1);
	return 0;
}


//Cleanup Module
void __exit CharDevice_exit(void)
{
	//dev_t Mydev;
	int MAJOR,MINOR;
	//Mydev=MKDEV(255,0);
	MAJOR=MAJOR(Mydev);
	MINOR=MINOR(Mydev);
	printk("\nThe Major Number is %d...THe Minor Number is %d\n",MAJOR,MINOR);
	unregister_chrdev_region(Mydev,4);//unregister the device numbers and the device created
	cdev_del(my_cdev);
	printk(KERN_ALERT "\nI have unregistered the stuff that was allocated.....Goodbye for ever.....\n");
	return;
}


//Open System Call
int NAME_open(struct inode *inode, struct file *filp)
{
	int Minor;
	struct file_operations *new_fops;
	
	printk(KERN_ALERT "\nThis is the Kernel....Open Call\n");
	new_fops = filp->f_op;	

	MyTestdev = inode->i_rdev;
	Minor = MINOR  (MyTestdev);
        down(&MySem);

	switch (Minor) {
	
		case 0:
			new_fops->read = NAME_read_add;
			new_fops->write = NAME_write_add;
			printk("\nAdd NEW FOPS is %p  AND FILEP is %p ",new_fops, filp);
			//filp->f_op->read = NAME_read_add;
			//filp->f_op->write = NAME_write_add;
			break;
		case 1: 
			new_fops->read = NAME_read_sub;
			new_fops->write = NAME_write_sub;
			printk("\nSub NEW FOPS is %p  AND FILEP is %p ",new_fops, filp);
			//filp->f_op->read = NAME_read_sub;
			//filp->f_op->write = NAME_write_sub;
			break;
		case 2: 
			new_fops->read = NAME_read_mul;
			new_fops->write = NAME_write_mul;
			printk("\nSub NEW FOPS is %p  AND FILEP is %p ",new_fops, filp);
			//filp->f_op->read = NAME_read_mul;
			//filp->f_op->write = NAME_write_mul;
			break;
		case 3: 
			new_fops->read = NAME_read_div;
			new_fops->write = NAME_write_div;
			printk("\nSub NEW FOPS is %p  AND FILEP is %p ",new_fops, filp);
			//filp->f_op->read = NAME_read_div;
			//filp->f_op->write = NAME_write_div;
			break;
		default:
			printk("\n Driver Not Existant");
			
	}

	
	return 0;
}

//Close System Call
int NAME_release(struct inode *indoe, struct file *filp)
{
        up (&MySem);

	printk(KERN_ALERT "\nThis is the release method of my Character Driver\n");
	return 0;
} 


//Write Functionality
ssize_t NAME_write_add(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
	char Kbuff[80];
	int *a=NULL,*b=NULL,result;
	ssize_t retval;
		
	result=copy_from_user((char *)Kbuff , (char *)Ubuff , count);
	if(result == 0)
	{
		printk(KERN_ALERT "\nMessage from the user......\n %s\n",Kbuff);
                printk(KERN_ALERT "\n %d bytes of data Successfully Written.....\n",count);
                retval=count;
		a=(int *)Kbuff;
		b = (int *)&Kbuff[4];
		add_result = *a + *b;
		printk ("\nSum is %d",add_result);
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
ssize_t NAME_read_add(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
	//char Kbuff[100]="Iam sending from Kernel buffer";
	int result;
	ssize_t retval=0;

	
	printk ("\nIn ADD_READ_Sum is %d",add_result);
	result=copy_to_user((char *)Ubuff,(const char *)&add_result,4);
	/*if(result == 0)
	{
		printk(KERN_INFO"copy to user space is successfully written%d\n",sizeof(Kbuff));
		retval = sizeof(Kbuff);
		return retval;
	}	
	else
        {
                printk(KERN_ALERT"\n Error Writing Data to User\n");
                retval=-EFAULT;
                return retval;
        }*/

	return retval;
}

ssize_t NAME_write_sub(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
	char Kbuff[80];
	int *a,*b,result;
	ssize_t retval;
		
	result=copy_from_user((char *)Kbuff , (char *)Ubuff , count);
	if(result == 0)
	{
		printk(KERN_ALERT "\nMessage from the user......\n %s\n",Kbuff);
                printk(KERN_ALERT "\n %d bytes of data Successfully Written.....\n",count);
                retval=count;
		a=(int *)Kbuff;
		b = (int *)&Kbuff[4];
		sub_result = *a - *b;
		printk ("\nSum is %d",sub_result);
                return retval;

	}
	else
	{
		printk(KERN_ALERT "\n Error Writing Data\n");
                retval=-EFAULT;
                return retval;

	}
}
ssize_t NAME_read_sub(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
	//char Kbuff[100]="Iam sending from Kernel buffer";
	int result;
	ssize_t retval=0;

	printk ("\nIn SUB_READ_Sum is %d",sub_result);
	result=copy_to_user((char *)Ubuff,(const char *)&sub_result,4);
	/*if(result == 0)
	{
		printk(KERN_INFO"copy to user space is successfully written%d\n",sizeof(Kbuff));
		retval = sizeof(Kbuff);
		return retval;
	}	
	else
        {
                printk(KERN_ALERT"\n Error Writing Data to User\n");
                retval=-EFAULT;
                return retval;
        }*/

	return retval;
}

ssize_t NAME_write_mul(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
	char Kbuff[80];
	int *a,*b,result;
	ssize_t retval;
		
	result=copy_from_user((char *)Kbuff , (char *)Ubuff , count);
	if(result == 0)
	{
		printk(KERN_ALERT "\nMessage from the user......\n %s\n",Kbuff);
                printk(KERN_ALERT "\n %d bytes of data Successfully Written.....\n",count);
                retval=count;
		a=(int *)Kbuff;
		b = (int *)&Kbuff[4];
		mul_result = (*a) * (*b);
		printk ("\nSum is %d",mul_result);
                return retval;

	}
	else
	{
		printk(KERN_ALERT "\n Error Writing Data\n");
                retval=-EFAULT;
                return retval;

	}
}
ssize_t NAME_read_mul(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
	//char Kbuff[100]="Iam sending from Kernel buffer";
	int result;
	ssize_t retval=0;

	printk ("\nIn MUL_READ_Sum is %d",mul_result);
	result=copy_to_user((char *)Ubuff,(const char *)&mul_result,4);
	/*if(result == 0)
	{
		printk(KERN_INFO"copy to user space is successfully written%d\n",sizeof(Kbuff));
		retval = sizeof(Kbuff);
		return retval;
	}	
	else
        {
                printk(KERN_ALERT"\n Error Writing Data to User\n");
                retval=-EFAULT;
                return retval;
        }*/

	return retval;
}
ssize_t NAME_write_div(struct file *filp, const char __user *Ubuff, size_t count, loff_t  *offp)
{
	char Kbuff[80];
	int *a,*b,result;
	ssize_t retval;
		
	result=copy_from_user((char *)Kbuff , (char *)Ubuff , count);
	if(result == 0)
	{
		printk(KERN_ALERT "\nMessage from the user......\n %s\n",Kbuff);
                printk(KERN_ALERT "\n %d bytes of data Successfully Written.....\n",count);
                retval=count;
		a=(int *)Kbuff;
		b = (int *)&Kbuff[4];
		div_result = *a / *b;
		printk ("\nSum is %d",div_result);
                return retval;

	}
	else
	{
		printk(KERN_ALERT "\n Error Writing Data\n");
                retval=-EFAULT;
                return retval;

	}
}

ssize_t NAME_read_div(struct file *filp, char __user *Ubuff, size_t count, loff_t  *offp)
{
	//char Kbuff[100]="Iam sending from Kernel buffer";
	int result;
	ssize_t retval=0;

	printk ("\nIn DIV_READ_Sum is %d",div_result);
	result=copy_to_user((char *)Ubuff,(const char *)&div_result,4);
	/*if(result == 0)
	{
		printk(KERN_INFO"copy to user space is successfully written%d\n",sizeof(Kbuff));
		retval = sizeof(Kbuff);
		return retval;
	}	
	else
        {
                printk(KERN_ALERT"\n Error Writing Data to User\n");
                retval=-EFAULT;
                return retval;
        }*/
	return retval;
	
}
//Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);
