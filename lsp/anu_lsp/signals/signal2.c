#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void sigalrm()
{
static int x=0;

printf("%s function invoked at %d time\n",__func__,x);
x++;
alarm(5);
}
void main()
{
signal(SIGALRM,sigalrm);
alarm(5);
while(1)
{
sleep(1);
printf("inside while\n");
signal(SIGINT, SIG_IGN);
}
}
