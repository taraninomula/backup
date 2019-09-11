#include<stdio.h>
int main()
{
int a,b,i,g;
printf("enter 2 numbers\n");
scanf("%d%d",&a,&b);
for(i=1;i<=a && i<=b;i++)
{
if(a%i==0 && b%i==0)
g=i;
}
printf("gcd is %d\n",g);
}
