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
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
//#include <linux/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */

MODULE_LICENSE("Dual BSD/GPL");

/* Declaration of memory.c functions */
int memory_open(struct inode *inode, struct file *filp);
int memory_release(struct inode *inode, struct file *filp);
ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t memory_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);
static void memory_exit(void);
static int memory_init(void);

/* Structure that declares the usual file */
/* access functions */
struct file_operations memory_fops = {
  .read = memory_read,
  .write =  memory_write,
  .open = memory_open,
  .release = memory_release
};

/* Global variables of the driver */
/* Major number */
int memory_major = 61;
/* Buffer to store data */
char *memory_buffer;

int memory_open(struct inode *inode, struct file *filp) {
printk(KERN_DEBUG "%s:%s:%d\n",__FILE__,__func__,__LINE__);
  return 0;
}

/* reading the device */
ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos) {

printk(KERN_INFO "%s:%s:%d,count:%d,*f_pos:%d\n",__FILE__,__func__,__LINE__,count,*f_pos);
/* The below printk enables kernel gives panic message */
printk ("memory_read *buf:%s \n",buf);

  /* Transfering data to user space */
copy_to_user(buf,memory_buffer,1);

if (*f_pos == 0) {
    *f_pos+=1;
    return 1;
  } else {
    return 0;
  }

//return 1;

}

/* writing to a device */
ssize_t memory_write( struct file *filp, char *buf, size_t count, loff_t *f_pos) {
printk(KERN_INFO "%s:%s:%d count:%d *f_pos:%d\n",__FILE__,__func__,__LINE__,count,*f_pos);

/* The below printk enables kernel gives panic message */
//printk ("memory_read *buf:%s \n",buf);

/* Transfering data to kernel space */
  copy_from_user(memory_buffer,buf,1);
  return 1;
}


/* close */ 
int memory_release(struct inode *inode, struct file *filp) {
printk(KERN_INFO "%s:%s:%d\n",__FILE__,__func__,__LINE__);
  return 0;
}

/* memory inital module */
static int memory_init(void) {
  int result;
  /* Registering device */
  result = register_chrdev(memory_major, "memory", &memory_fops);
  if (result < 0) {
    printk("memory: cannot obtain major number %d\n", memory_major);
    return result;
  }
  /* Allocating memory for the buffer */
  memory_buffer = kmalloc(1, GFP_KERNEL);
  if (!memory_buffer) {
    result = -ENOMEM;
    goto fail;
  }
  memset(memory_buffer, 0, 1);
  printk("Inserting memory module\n");
  return 0;
  fail:
    memory_exit();
    return result;
}

/* memory exit module */
static void memory_exit(void) {
  /* Freeing the major number */
  unregister_chrdev(memory_major, "memory");
  /* Freeing buffer memory */
  if (memory_buffer) {
    kfree(memory_buffer);
  }
  printk("Removing memory module\n");
}


/* Declaration of the init and exit functions */
module_init(memory_init);
module_exit(memory_exit);
