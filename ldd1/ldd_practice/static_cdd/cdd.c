/*static cdd example*/
#include<linux/fs.h>/*file operations*/
#include<linux/kernel.h>/*printk def*/
#include <linux/cdev.h>/*cdev*/
#include <asm/uaccess.h>/*copy to/from user*/
#include <linux/init.h>//Required header for the Intialization and Cleanup Functionalities....
#include <linux/module.h>//This Header contains the necessary stuff for the Module
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */

#define NAME "static_char"
#define MYMAJOR 60

ssize_t my_read (struct file *, char __user *, size_t, loff_t *);
ssize_t my_write (struct file *, const char __user *, size_t, loff_t *);
int my_open (struct inode *, struct file *);
int my_close (struct inode *, struct file *);

struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_close
};

struct cdev *my_cdev;
dev_t devno;
//devno=MKDEV(MYMAJOR,0);
char Ubuf[1024],Kbuf[1024];

static int CharDevice_init(void)
{
printk("chardevice_init()...........\n");
devno=MKDEV(MYMAJOR,0);
register_chrdev_region(devno,1,NAME);
my_cdev = cdev_alloc();//allocate memory to Char Device structure
my_cdev->ops = &fops;//link our file operations to the char device
cdev_add(my_cdev,devno,1);//Notify the kernel abt the new device
return 0;
}

static void CharDevice_exit(void)
{
printk("CharDevice_exit().............\n");
unregister_chrdev_region(devno,1);
cdev_del(my_cdev);
}

int my_open (struct inode *inode, struct file *file)
{
printk("my_open.........................\n");
return 0;
}
ssize_t my_read (struct file *file, char __user *Ubuf, size_t count, loff_t *offset)
{
printk("my_read......................\n");
copy_to_user(Ubuf,Kbuf,count);
printk("%s\n",Ubuf);
return (ssize_t)count;
}

ssize_t my_write (struct file *file, const char __user *Ubuf, size_t count, loff_t *offset)
{
printk("my_write....................\n");
copy_from_user( Kbuf,Ubuf,count);
printk("%s\n",Kbuf);
return (ssize_t)count;
}

int my_close (struct inode *inode, struct file *file)
{
printk("my_close....................\n");
return 0;
}

module_init(CharDevice_init);
module_exit(CharDevice_exit);
