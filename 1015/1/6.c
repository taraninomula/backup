/*#include<stdio.h>
int main()
{
int a,b,c;
printf("enter 2 numbers\n");
scanf("%d%d",&a,&b);
int gcd(int a,int b);
c=gcd(a,b);
printf(" gcd is %d\n",c);
}
	int gcd(int a,int b)
	{
		if(a==b)
		return b;
		else if(a>b)
		return gcd(a-b,b);
		else if(a<b)
		return gcd(a,b-a);
	}

*/
#include<stdio.h>
int main()
{
int a,b,t;
printf("enter 2 numbers\n");
scanf("%d%d",&a,&b);
while(a!=b)
{
if(a<b)
{
t=a;
a=b;b=t;
}
else
a=a-b;
}
printf("%d\n",a);
}
