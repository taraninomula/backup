#include<stdio.h>
int power(int n,int i)
{
	int j;
	if(i!=0)
	{
		for(j=1;j<i;j++)
		{
			n=n*2;
		}
		return n;
	}
	else
		return 1;
}
int main()
{
	int n,sum=0,i=0,a;
	printf("enter a number\n");
	scanf("%d",&n);
	while(n)
	{
		a=n%10;
		sum=sum+a*power(2,i);
		n=n/10;
		i++;
	}
	printf("%d\n",sum);
}

