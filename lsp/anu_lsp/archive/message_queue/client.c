#include<stdio.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/msg.h>
struct msgbuf
{
	long mtype;
	char mtext[100];
};
int main()
{
	int id;
	struct msgbuf clibuf;
	while(1)
	{
	id=msgget(8,0);
	if(id==-1)
		perror("msgget\n");
	//recieving message from server
	if(msgrcv(id,&clibuf,sizeof(clibuf.mtext),4,0)==-1)
		perror("msgrcv\n");
	printf("message from server ; %s\n",clibuf.mtext);
	//sending message to client
	clibuf.mtype=7;
	printf("enter message to server\n");
	scanf("%s",clibuf.mtext);
	if(msgsnd(id,&clibuf,sizeof(clibuf.mtext),0)==-1)
		perror("msgsnd\n");sleep(1);
}
}
