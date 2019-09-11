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


#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include "convenient.h"

static struct work_struct ws;

static void wq_func(void)
{
	MSG("We're here!\n");
}

static int workq_demo_init(void)
{
	INIT_WORK(&ws, wq_func);
	MSG("Now sleeping for 3s...\n");
	DELAY_SEC(3);
	schedule_work(&ws);
	//schedule_delayed_work(&ws, 3*HZ);

	MSG("Installed.\n");
	return 0;
}

static void workq_demo_exit(void)
{
	flush_scheduled_work ();
	MSG("Removed.\n");
}

MODULE_LICENSE("GPL");

module_init(workq_demo_init);
module_exit(workq_demo_exit);

