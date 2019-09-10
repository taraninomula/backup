#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define KEY 32
#define SIZE 1054

int main()
{
	int shmid;
	char *ptr=NULL;
	//while(1)
	//{
		shmid=shmget(KEY,SIZE,0);
		if(shmid==-1)
		{
			printf("shared memory accessing error\n");
			return 0;
		}
		ptr=shmat(shmid,0,0);
		if(ptr==(char*)-1)
		{
			printf("invalid address\n");
			return 0;
		}
	
		printf("address is : %p\n",ptr);
		printf("Reading data from shared memory is ");
		printf("from server=%s\n",ptr);
	//	printf("write data to send to server\n");
	//	scanf("%s",ptr);
	//}
		shmdt(ptr);
		return 0;

}
