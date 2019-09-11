/* static waitq

In this source code, two places we are sending wake up. One from read function and another one from driver exit function.

I’ve created one thread (wait_function) which has while(1). That thread will always wait for the event. It will be sleep until it gets wake up call. When it gets the wake up call, it will check the condition. If condition is 1 then the wakeup came from read function. It it is 2, then the wakeup came from exit function. If wake up came from read, it will print the read count  and it will again wait.If its from exit function, it will exit from the thread.

steps to run this code

    Build the driver by using Makefile (sudo make)
    Load the driver using sudo insmod driver.ko
    Then Check the Dmesg

    Major = 246 Minor = 0
    Thread Created successfully
    Device Driver Insert…Done!!!
    Waiting For Event…

    So that thread is waiting for the event. Now we will send the event by reading the driver using sudo cat /dev/etx_device
    Now check the dmesg

    Device File Opened…!!!
    Read Function
    Event Came From Read Function – 1
    Waiting For Event…
    Device File Closed…!!!

    We send the wake up from read function, So it will print the read count and then again it will sleep. Now send the event from exit function by sudo rmmod driver

    Event Came From Exit Function
    Device Driver Remove…Done!!!

    Now the condition was 2. So it will return from the thread and remove the driver.
*/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>                 //kmalloc()
#include <linux/uaccess.h>              //copy_to/from_user()

#include <linux/kthread.h>
#include <linux/wait.h>                // Required for the wait queues


uint32_t read_count = 0;
static struct task_struct *wait_thread;

DECLARE_WAIT_QUEUE_HEAD(wait_queue_etx);

dev_t dev = 0;
static struct class *dev_class;
static struct cdev etx_cdev;
int wait_queue_flag = 0;

static int __init etx_driver_init(void);
static void __exit etx_driver_exit(void);

/*************** Driver Fuctions **********************/
static int etx_open(struct inode *inode, struct file *file);
static int etx_release(struct inode *inode, struct file *file);
static ssize_t etx_read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t etx_write(struct file *filp, const char *buf, size_t len, loff_t * off);

static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = etx_read,
        .write          = etx_write,
        .open           = etx_open,
        .release        = etx_release,
};

static int wait_function(void *unused)
{
        
        while(1) {
                printk(KERN_INFO "Waiting For Event...\n");
                wait_event_interruptible(wait_queue_etx, wait_queue_flag != 0 );
                if(wait_queue_flag == 2) {
                        printk(KERN_INFO "Event Came From Exit Function\n");
                        return 0;
                }
                printk(KERN_INFO "Event Came From Read Function - %d\n", ++read_count);
                wait_queue_flag = 0;
        }
        do_exit(0);
        return 0;
}



static int etx_open(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Opened...!!!\n");
        return 0;
}

static int etx_release(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Closed...!!!\n");
        return 0;
}

static ssize_t etx_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Read Function\n");
        wait_queue_flag = 1;
        wake_up_interruptible(&wait_queue_etx);
        return 0;
}
static ssize_t etx_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Write function\n");
        return 0;
}




static int __init etx_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "etx_Dev")) <0){
                printk(KERN_INFO "Cannot allocate major number\n");
                return -1;
        }
        printk(KERN_INFO "Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));

        /*Creating cdev structure*/
        cdev_init(&etx_cdev,&fops);
        etx_cdev.owner = THIS_MODULE;
        etx_cdev.ops = &fops;

        /*Adding character device to the system*/
        if((cdev_add(&etx_cdev,dev,1)) < 0){
            printk(KERN_INFO "Cannot add the device to the system\n");
            goto r_class;
        }

        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"etx_class")) == NULL){
            printk(KERN_INFO "Cannot create the struct class\n");
            goto r_class;
        }

        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"etx_device")) == NULL){
            printk(KERN_INFO "Cannot create the Device 1\n");
            goto r_device;
        }
        
        //Initialize wait queue
        init_waitqueue_head(&wait_queue_etx);

        //Create the kernel thread with name 'mythread'
        wait_thread = kthread_create(wait_function, NULL, "WaitThread");
        if (wait_thread) {
                printk("Thread Created successfully\n");
                wake_up_process(wait_thread);
        } else
                printk(KERN_INFO "Thread creation failed\n");

        printk(KERN_INFO "Device Driver Insert...Done!!!\n");
    return 0;

r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}

void __exit etx_driver_exit(void)
{
        wait_queue_flag = 2;
        wake_up_interruptible(&wait_queue_etx);
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&etx_cdev);
        unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Device Driver Remove...Done!!!\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbeTronicX <embetronicx@gmail.com or admin@embetronicx.com>");
MODULE_DESCRIPTION("A simple device driver");
MODULE_VERSION("1.7");
