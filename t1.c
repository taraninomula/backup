#include<stdio.h>
int main()
{
	int a=1,b=2,c=3;
	int *p1=&a,*p2=&b,*p3=&c;
	int **sp=&p1;
	*sp=p2;

}




