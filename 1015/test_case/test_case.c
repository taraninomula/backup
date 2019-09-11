#include<stdio.h>
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
	freopen("/home/nomultar/1015/test_case/input.txt","r",stdin);
	int a,b,c;
	scanf("%d%d",&a,&b);
	c=a+b;
	printf("%d\n",c);
	}
}
