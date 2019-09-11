#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<string.h>
#define KEY 32
#define SIZE 512
int main()
{
	int shmid,semid,ctl1,ctl2;
	char *ptr,*addr;
	struct sembuf semope;

	shmid=shmget(KEY,SIZE,0777 | IPC_CREAT);
	if(shmid==-1)
		printf("shared memory creation failed\n");
	addr=shmat(shmid,0,0);
	if(addr==(char *)-1)
		printf("attach failed\n");
	semid=semget(KEY,2,0777 | IPC_CREAT);
	if(semid==-1)
		printf("semaphore failed\n");
	ctl1=semctl(semid,0,SETVAL,0);
	ctl2=semctl(semid,1,SETVAL,0);
	while(1)
	{
		//first counter
		semope.sem_num=0;
		semope.sem_op=-1;
		semope.sem_flg=0;
		semop(semid,&semope,1);
		printf("from client : %s\n",addr);

		printf("enter data to send to client\n");
		scanf("%s",addr);
		//strcpy(addr,ptr);
		//second counter
		semope.sem_num=1;
		semope.sem_op=1;
		semope.sem_flg=0;
		semop(semid,&semope,1);
	}
}
		
	
	

