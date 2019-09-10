#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define KEY 32
#define SIZE 1054
int main()
{
	int shmid;
	char *addr=NULL;
	while(1)
	{
	shmid=shmget(KEY,SIZE,0777|IPC_CREAT);
	if(shmid==-1)
	{
		printf("shared memory is not created\n");
		return 0;
	}
	addr=shmat(shmid,0,0);
	//printf("address is : %p\n",addr);
	if(addr==(char*)-1)
	{
		printf("invalid address\n");
		return 0;
	}
	printf("writting data to shared memory\n");
	scanf("%s",addr);
	}
	return 0;
}
