#include<stdio.h>
int main()
{
	int n,sum=0,a;
	printf("enter a number\n");
  	scanf("%d",&n);
	while(n!=0)
	{
		a=n%10;
		sum=sum*10+a;
		n=n/10;
	}
	printf("reversed number is %d\n",sum);
}
	
	
