#include<stdio.h>
int main()
{
	int x,p;
	printf("enter number and position to be checked\n");
	scanf("%d%d",&x,&p);
	if((0x1<<p)&x)
		printf("set\n");
	else
		printf("clear\n");

		
}

