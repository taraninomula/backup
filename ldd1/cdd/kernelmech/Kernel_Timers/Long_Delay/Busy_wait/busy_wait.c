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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

static __init int myinit(void)
{
	unsigned long j = jiffies + 10*HZ;
	printk("Try to do something for the next 10 seconds.\n");
	printk("I am putting the system off to a standstill for the\n"
	       "next 10 seconds");
	while( jiffies < j ) { 
		
                }
	printk("Now I am out of the loop");
	return -1; /* dont load the module */
}

static __exit void myexit(void)
{
printk("\nModule Successfully removed");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kernel Masters");
MODULE_DESCRIPTION ("Example: Kernel Long Delays");

module_init(myinit);
module_exit(myexit);



