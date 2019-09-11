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
#include "export.h"

static int two_init(void)
{
        int ret;
//	leave_sem();
       ret = get_sem();
       /* if(ret == 0) {
                printk("module two got the semaphore\n");
                return 0;
        } else {
                printk("could not get the semaphore\n");
                return -EPERM;
        }*/
	printk("unlock\n");
}

static void two_exit(void)
{
        printk("module two leaving the semaphore\n");
        leave_sem();
}

module_init(two_init);
module_exit(two_exit);

MODULE_LICENSE("GPL");


