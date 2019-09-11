#include<stdio.h>
int main()
{
	int x,p,s,c,t;
	printf("enter number and position\n");
	scanf("%d%d",&x,&p);
	s=((0x1<<p)|x);
	printf("after setting %d\n",s);
	c=((~(0x1<<p))&x);
	printf("after clearing %d\n",c);
	
	c=(((0x1<<p))^x);
	printf("after toggling %d\n",c);
}

