#include<stdio.h>
struct student
{
	unsigned int a :3;
	unsigned int b :2;
};
int main()
{
	struct student x;
	x.a=7;
	x.b=2;
	printf("%d %d\n",x.a,x.b);

}
