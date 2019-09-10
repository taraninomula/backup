#include<stdio.h>
int main()
{
	unsigned int n,r=0;
	printf("enter a number\n");
	scanf("%u",&n);
	unsigned int i;
	unsigned int s=sizeof(n)*8;
	for(i=0;i<s;i++)
	{
		if(n&(0x1<<i))
			r=r|(0x1<<(s-i-1));
		else
			r=r&(~(0x1<<(s-i-1)));
	}
	printf("reversed number is %u\n",r);

}
