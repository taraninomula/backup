#include<stdio.h>
int main()
{
	int n,p;
	printf("enter a number\n");
	scanf("%d",&n);
	printf("enter position\n");
	scanf("%d",&p);
	n=n&(~(0x1<<p));
	printf("after masking  n is %d\n",n);
}

