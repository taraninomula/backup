#include<stdio.h>
int main()
{
int n,m,t;
printf("enter the range\n");
scanf("%d%d",&n,&m);
void prime(int n,int m);
if(n>m)
{
t=n;
n=m;
m=t;
}
prime(n,m);
}
void prime(int n,int m)
{
int c=0,i;
if(n>m)
return;
else
{
for(i=1;i<=n;i++)
{
if(n%i==0)
c++;
}
if(c==2)
printf("%d\t",n);
n++;
prime(n,m);
}
}
