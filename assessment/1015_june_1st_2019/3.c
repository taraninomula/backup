#include<stdio.h>
int main()
{
	int n,p;
	printf("enter a number\n");
	scanf("%d",&n);
	printf("enter the position to reset\n");
	scanf("%d",&p);
	n=n&(~(0x1<<p));
	printf("after reversing n is %d\n",n);
}
	
