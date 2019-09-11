/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page   : www.facebook.com/kernelmasters                   *
 *                                                                         *
 *  Conducting Workshops on - Embedded Linux & Device Drivers Training.    *
 *  -------------------------------------------------------------------    *
 *  Tel : 91-9949062828, Email : kernelmasters@gmail.com                   *
 *  www.kernelmasters.org                                                                       *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation. No warranty is attached; we cannot take *
 *   responsibility for errors or fitness for use.                         *
 ***************************************************************************/

/* Necessary includes for drivers */
#include <linux/init.h>
//#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/ioport.h>
//#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */
#include <asm/io.h> /* inb, outb */
#include <linux/interrupt.h>

#define HW_LEN 80
#define IRQ_7 7
#define TEST_DEV "myIntDev"

MODULE_AUTHOR ("Kernel Masters");
MODULE_DESCRIPTION ("JOC: Android for Embedded Systems, KPHB, Hyderabad");
MODULE_LICENSE("Dual BSD/GPL");
/* Function declaration of parlelport.c */
int parlelport_open(struct inode *inode, struct file *filp);
int parlelport_release(struct inode *inode, struct file *filp);
ssize_t parlelport_read(struct file *filp, char *buf,
                       size_t count, loff_t *f_pos);
ssize_t parlelport_write(struct file *filp, char *buf,
                       size_t count, loff_t *f_pos);
void parlelport_exit(void);
int parlelport_init(void);

void do_mytasklet (unsigned long);
DECLARE_TASKLET (my_tasklet, do_mytasklet, 0);
static int isrCnt=0;

/* Structure that declares the common */
/* file access fcuntions */
struct file_operations parlelport_fops = {
  read: parlelport_read,
  write: parlelport_write,
  open: parlelport_open,
  release: parlelport_release
};


/* Driver global variables */
/* Major number */
int parlelport_major = 61;
/* Control variable for memory */
/* reservation of the parallel port*/
int port;
module_init(parlelport_init);
module_exit(parlelport_exit);

void do_mytasklet (unsigned long unused)
{
printk ("This message from tasklet\n");
}

static irqreturn_t myIntHandler (int irq, void *dev_id) //, struct pt_regs *regs)
{
tasklet_schedule(&my_tasklet);
isrCnt++;
return IRQ_HANDLED;
}

int parlelport_init(void) {
  int result,rv;
  /* Registering device */
  result = register_chrdev(parlelport_major, "parlelport",
      &parlelport_fops);
  if (result < 0) {
    printk(
      "<1>parlelport: cannot obtain major number %d\n",
      parlelport_major);
    return result;
  }

  //parlelport modified init module
  /* Registering port */
	port = check_region(0x378, 3);
	if (port) {
  	printk("<1>parlelport: cannot reserve 0x378\n");
  	result = port;
 	goto fail;
	}
request_region(0x378, 3, "parlelport");

rv = request_irq(IRQ_7, myIntHandler,IRQF_TRIGGER_RISING ,TEST_DEV,NULL);
if (rv )
{

 printk ("<1>can't get interrupt %d\n",IRQ_7);

}
outb(0x10,0x37A);
  printk("<1>Inserting parlelport module\n");
  return 0;
  fail:
    parlelport_exit();
    return result;
}

void parlelport_exit(void) {
  /* Make major number free! */
  unregister_chrdev(parlelport_major, "parlelport");
  outb(0x00,0x37A);
 
  //parlelport modified exit module>
  /* Make port free! */
  if (!port) {
  release_region(0x378,1);
  }
  free_irq(IRQ_7,NULL);
  printk("<1>Removing parlelport module\n");
}


int parlelport_open(struct inode *inode, struct file *filp) {
  /* Success */
  return 0;
}

int parlelport_release(struct inode *inode, struct file *filp) {
  /* Success */
  return 0;
}

ssize_t parlelport_read(struct file *filp, char *buf,
  size_t count, loff_t *f_pos) {
  /* Buffer to read the device */
  char parlelport_buffer;
  //parlelport inport
  /* Reading port */	
	parlelport_buffer = inb(0x378);

  /* We transfer data to user space */
  copy_to_user(buf,&parlelport_buffer,1);
  /* We change the reading position as best suits */
  if (*f_pos == 0) {
    *f_pos+=1;
    return 1;
  } else {
    return 0;
  }
}


ssize_t parlelport_write( struct file *filp, char *buf,
  size_t count, loff_t *f_pos) {
  char *tmp;
  /* Buffer writing to the device */
  char parlelport_buffer;
  tmp=buf+count-1;
  copy_from_user(&parlelport_buffer,tmp,1);
  //parlelport outport
  /* Writing to the port */
  outb(parlelport_buffer,0x378);
  return 1;
}

