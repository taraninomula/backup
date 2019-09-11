#include<stdio.h>
#include<unistd.h>
int main()
{
pid_t child;
int a,b;
a=10;
b=20;
child=fork();
a=a+b;
if(child>0)
{
printf("%d\n",a);
}
return 0;
}
