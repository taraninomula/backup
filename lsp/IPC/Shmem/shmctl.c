
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

main()
{
	int shmid;
	
	if((shmid=shmget(10,0,0))==-1) {
		perror("shmid");
		exit(1);
	}
	
	if(shmctl(shmid,IPC_RMID,0)==-1) {
		perror("shmctl");
		exit(1);
	}

	
	printf("Shared memory successfully removed\n");
}
