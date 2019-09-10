#include<stdio.h>
#include<math.h>
int down_zero(int n);
int mid_factor(int n);
int min(int a,int b);
int main()
{
	int n,c;
	printf("enter number\n");
	scanf("%d",&n);
	c=down_zero(n);
	printf("%d\n",c);
}
int down_zero(int n)
{
	int c,i,m=0;
	if(n==0)
		return 0;
	for(i=1;i<=sqrt(n);i++)
	{
		if(n%i==0)
		{
			if(i!=1)
				c=down_zero(n/i)+1;
			else
				c=down_zero(n-1)+1;
		}
		if(m==0)
			m=c;
		if(c<m)
			m=c;
	}
	return m;
}
int max(int a,int b)
{
        if(a>b)
                return a;
        else
                return b;
}

int mid_factor(int n)
{
	int m,i,j=0,a[100];
	for(i=1;i<=n; i++)
	{
		if (n%i == 0)
		{
			a[j]=i;
			j++;
		}
	}
	if(j%2==0)
		m=a[(j/2)-1];
	else
		m=a[(j/2)];
	return m;
}
