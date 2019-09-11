#include <stdio.h>
#include "km.h" 

int km1_open (int x);
int km1_read (int z);
void fun_km2(void);
struct  file_ops km1 = {
 	"KM1_Driver",
	.open = km1_open,
	.read = km1_read,
};

int km1_open (int x)
{
	printf("km1_open:%d\n",x);
}

int km1_read (int z)
{
	printf("km1_read:%d\n",z);
}

main ()
{
struct file_ops *fops1 = &km1;
printf("driver name:%s\n",fops1->d_name);
fops1->open(5);
fops1->read(8);
fun_km2();
}





