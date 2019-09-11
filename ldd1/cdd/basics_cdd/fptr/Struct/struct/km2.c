#include<stdio.h>
#include "km.h"

int km2_open(int );
int km2_read(int );


struct file_ops km2_ops = {
	.open = km2_open,
	.read = km2_read,
};

int km2_open(int x)
{
	printf ("This is km2_open x:%d\n",x);
	return 0;	
}


int km2_read(int x)
{
	printf ("This is km2_read x:%d\n",x);
	return 0;	
}

void fun_km2 (void)
{
	struct file_ops *fptr;
	fptr = &km2_ops;
        fptr->open(3); 	
        fptr->read(4); 

}


