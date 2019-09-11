/***************************************************************************
 *      Organisation    : Kernel Masters, KPHB, Hyderabad, India.          *
 *      facebook page   : www.facebook.com/kernelmasters                   *
 *                                                                         *
 *  Conducting Workshops on - Embedded Linux & Device Drivers Training.    *
 *  -------------------------------------------------------------------    *
 *  Tel : 91-9949062828, Email : kernelmasters@gmail.com                   *
 *  www.kernelmasters.org                                                  *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation. No warranty is attached; we cannot take *
 *   responsibility for errors or fitness for use.                         *
 ***************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>


int id;
int count;

irqreturn_t handler(int irq, void *id)
{

	printk("inside the handler\n");
        count++;
        printk("The count is %d \n",count);
        return IRQ_HANDLED;
}

int init_module(void)
{
	int rv;
	printk("simple modules loaded\n");
	rv = request_irq(1, handler, IRQF_SHARED, "kernelmasters", &id); 	
        if (rv )
        {
                printk ("<1>can't get interrupt 1\n");
       		return -1;
        }

        return 0;
}

void cleanup_module(void)
{
	printk("simple module unloaded\n");
	free_irq(1, &id);			
}
MODULE_AUTHOR ("Kernel Masters");
MODULE_DESCRIPTION ("JOC: Android for Embedded Systems, KPHB, Hyderabad");
MODULE_LICENSE("GPL");

