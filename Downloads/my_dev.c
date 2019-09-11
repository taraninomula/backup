#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>
 
static dev_t first; // Global variable for the first device number 
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class


static irqreturn_t sample_irq(int irq, void *dev_id)
{    
	printk("im in handler function\n");

	return 0;
    /* now `dev' points to the right hardware item */    /* .... */
}


static int my_open(struct inode *i, struct file *f)
{
	int ret;
	printk(KERN_INFO "Driver: open()\n");
	ret = request_irq(50, sample_irq, 0, "sample", 0);
	if (ret < 0) {
		printk(KERN_ALERT ": request_irg failed with \n");
		return -EBUSY;
	}
	
  	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	printk(KERN_INFO "Driver: close()\n");
	return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver: read()\n");
	return 0;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	printk(KERN_INFO "Driver: write()\n");
	return len;
}

static struct file_operations pugs_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write
};
 
static int __init my_init(void) /* Constructor */
{
	printk("Namaskar: mydev registered\n");

	if (alloc_chrdev_region(&first, 0, 1, "VT_CAMARA") < 0){
		return -1;
  	}

	if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL) {
		unregister_chrdev_region(first, 1);
    		return -1;
	}
    	if (device_create(cl, NULL, first, NULL, "mynull") == NULL) {
    		class_destroy(cl);
    		unregister_chrdev_region(first, 1);
    		return -1;
  	}

	cdev_init(&c_dev, &pugs_fops); /*initialise the character device structure*/
	/* hand this structure to the VFS using the call cdev_add() */
    	if (cdev_add(&c_dev, first, 1) == -1) {
		device_destroy(cl, first);
    		class_destroy(cl);
    		unregister_chrdev_region(first, 1);
    		return -1;
 	}

	return 0;
}
 
static void __exit my_exit(void) /* Destructor */
{
	cdev_del(&c_dev);
	device_destroy(cl, first);
	class_destroy(cl);
	unregister_chrdev_region(first, 1);

	printk("Alvida: mydev unregistered\n");
}
 
module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VT");
MODULE_DESCRIPTION("Our First Character Driver");
