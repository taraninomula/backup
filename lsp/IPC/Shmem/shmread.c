
#include <stdio.h>
#include <stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>

main()
{
	int shmid;
	char *msg;
	
	if((shmid=shmget(0,1024,0))==-1) {
		perror("shmget");
		exit(1);
	}

	msg=shmat(shmid,0,0);
	
	printf("Data written in the shared memory is:%s\n",msg);

	getchar();
	shmdt(msg);
}
	
/**/	
