#include<stdio.h>
#include "km.h"

int km1_open(int );
int km1_read(int );

struct file_ops km1_ops = {
	.open = km1_open,
	.read = km1_read,
};

int km1_open(int x)
{
	printf ("This is km1_open x:%d\n",x);
	return 0;	
}


int km1_read(int x)
{
	printf ("This is km1_read x:%d\n",x);
	return 0;	
}

main ()
{
	struct file_ops *fptr;
	fptr = &km1_ops;
        fptr->open(1); 	
        fptr->read(2); 
	
	fun_km2();

}

