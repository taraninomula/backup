#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
struct msgbuf
{
    long    mtype;
    char    mtext[20];
};
main()
{
int msgid;
struct msgbuf rbuf;
msgid=msgget(1,0666|IPC_CREAT);
if(msgid<0)
puts("queue is not created");
msgrcv(msgid,&rbuf,20,2,0);
printf("Reading data from Queue is %s\n",rbuf.mtext);
rbuf.mtype=3;
puts("Taking input from user");
scanf("%s",rbuf.mtext);
msgsnd(msgid,&rbuf,20,0);
printf("sending data to Queue  \n");
}
