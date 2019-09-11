#include<stdio.h>
static int x=9;
int main()
{
	int x=5;
	{
	int x=2;
	}
	printf("%d\n",x);
}
