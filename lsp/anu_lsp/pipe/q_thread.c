#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<pthread.h>

#define KEY 1
#define TYPE1 12
#define TYPE2 21

void client(void *ptr);
void server(void *ptr);
struct msgbuf
{
    long    mtype;
    char    mtext[20];
};

//struct msgbuf rbuf;
//struct msgbuf cbuf;
int msgid;
int main()
{
	pthread_t tid1,tid2;
	int id1,id2;
	msgid=msgget(KEY,0666 | IPC_CREAT);
	if(msgid<0)
	puts("Queue is not created");
       
		id1=pthread_create(&tid1,NULL,client,NULL);
		id2=pthread_create(&tid2,NULL,server,NULL);
		//printf("pthread_create() for thread 1 returns: %d\n",tid1);
		//printf("pthread_create() for thread 2 returns: %d\n",tid2);
       
		     pthread_join(tid1,NULL);
		     pthread_join(tid2,NULL);
                
       
}
void client(void *ptr)
{
	struct msgbuf cbuf;
       
	cbuf.mtype=2;
	puts("client");
	puts("client Taking input from user");
	scanf("%s",cbuf.mtext);
	msgsnd(msgid,&cbuf,20,0);
	printf("client sending data to Queue  \n");
	cbuf.mtype=3;
	msgrcv(msgid,&cbuf,20,3,0);
	printf("client Reading data from Queue is %s\n",cbuf.mtext);

	
}
void server(void *ptr)
{
	struct msgbuf rbuf;
       
	puts("server");
	msgrcv(msgid,&rbuf,20,2,0);
	printf("Server Reading data from Queue is %s\n",rbuf.mtext);
        rbuf.mtype=3;
	puts("server enter data");
	scanf("%s",rbuf.mtext);
        printf("server sending data to Queue  \n");
	msgsnd(msgid,&rbuf,20,0);
	

	

}
