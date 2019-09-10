#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#define KEY 32
#define SIZE 512

int main()
{
	int shmid,semid,ctl1,ctl2;
	char *addr;
	struct sembuf semope;
	shmid=shmget(KEY,SIZE,0);
	if(shmid==-1)
		printf("shared memory creation failed\n");
	addr=shmat(shmid,0,0);
	if(addr==(char *)-1)
		printf("attach failed\n");
	semid=semget(KEY,2,0);
	if(semid==-1)
		printf("semaphore failed\n");
	while(1)
	{
		printf("enter data to server\n");
		scanf("%s",addr);
		//counter 1
		semope.sem_num=0;
		semope.sem_op=1;
		semope.sem_flg=0;
		semop(semid,&semope,1);
		//counter 2
		semope.sem_num=1;
		semope.sem_op=-1;
		semope.sem_flg=0;
		semop(semid,&semope,1);
		printf("from server : %s\n",addr);
	}
}

