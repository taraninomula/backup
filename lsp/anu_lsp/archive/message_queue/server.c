#include<stdio.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/msg.h>
#include<string.h>
struct msgbuf
{
	long mtype;
	char mtext[100];
};
int main()
{
	int id;
	struct msgbuf serbuf;
	while(1)
	{
	id=msgget(8,IPC_CREAT|0666);
	if(id==-1)
		perror("msgget\n");
	serbuf.mtype=4;
	//sending message to client
	printf("enter msg to client\n");
	scanf("%s",serbuf.mtext);
	if(msgsnd(id,&serbuf,sizeof(serbuf.mtext),0)==-1)
		perror("msgsnd\n");sleep(1);
	//recieving message from client
	if(msgrcv(id,&serbuf,sizeof(serbuf.mtext),7,0)==-1)
		perror("msgrcv\n");
	printf("from client : %s\n",serbuf.mtext);
}
}
	



