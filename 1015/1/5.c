#include<stdio.h>
int c=0,i=1;
int main()
{
int n,m,t,j;
printf("enter the range\n");
scanf("%d%d",&n,&m);
j=n;
if(n>m)
{
t=n;
n=m;
m=t;
}
int isprime(int j,int i);
while(j<=m)
	{
	isprime(j,i);
	if(c==2)
	printf("%d\t",j);
	j++;
	}
}
	int isprime(int j,int i)
	{
		
		if(j>=i)
		{
			if(j%i==0)
			c++;
			isprime(j,++i);
		}
	return c;
	}
