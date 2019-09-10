#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include <string.h>
void sigalrm()
{
static int x=0;

printf("%s function invoked at %d time\n",__func__,x);
x++;
alarm(5);
}
void main()
{
struct sigaction act;
memset(&act,0,sizeof(act));
act.sa_handler=sigalrm;
sigaction(SIGALRM,&act,NULL);
alarm(5);
while(1)
{
sleep(1);
printf("inside while\n");
signal(SIGINT, SIG_DFL);

}
int i=0;
sigset_t s_set;
signal(62,sigalrm);
signal(4,sigalrm);
sigemptyset(&s_set);
sigaddset(&s_set,62);
sigaddset(&s_set,4);
//sigprocmask(SIG_BLOCK|SIG_SETMASK,&s_set,NULL);
//printf("signals are blocked\n");
while(i<100)
i++;
sigprocmask(SIG_UNBLOCK,&s_set,NULL);
printf("signals are unblocked\n");
while(1);
}
