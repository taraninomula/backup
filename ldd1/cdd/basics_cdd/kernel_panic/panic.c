#include<linux/module.h>  // module_init(), module_exit()
#include<linux/init.h> // MODULE_AUTHOR()
#include<linux/kernel.h> // printk
#include<linux/sched.h>

MODULE_AUTHOR("Kernel Masters");
MODULE_DESCRIPTION("Hello World template");
MODULE_LICENSE("GPLV2");

int *ptr=NULL;

static int panic_init(void) {
	printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
	printk("pid:%d comm:%s\n",current->pid,current->comm);
	printk("%d\n",*ptr); //creates kernel panic
	return 0;
}

static void panic_exit(void) {
	printk("%s:%s:%d\n",__FILE__,__func__,__LINE__);
}

module_init(panic_init);
module_exit(panic_exit);
