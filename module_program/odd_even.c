#include<linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("Dual BSD/GPL");
void even(void)
{
	int i;
	for(i=0;i<50;i++)
	{
		if(i%2==0)
			printk("%d\t",i);
	}
}
void odd(void)
{
	int i;
	for(i=0;i<50;i++)
	{
		if(i%2!=0)
			printk("%d\t",i);
	}
}
static int my_init(void)
{
	printk("even numbers\n");
	even();
	printk("\n");
	printk("odd numbers\n");
	odd();
	printk("\n");
}
static void my_exit(void)
{
	printk("Exiting function\n");
}
module_init(my_init);
module_exit(my_exit);


