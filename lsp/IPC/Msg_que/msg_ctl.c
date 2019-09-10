#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/msg.h>
    
# define KEY	555

   struct mesg{
   long int type;
	char msg[20];
    };

main()
{
    	struct mesg message;
	int qid, n;
//	system("clear");
    	qid = msgget(KEY, 0666);
	if (qid < 0) {
		perror("msgget");
		exit(0);
    	}
	if ((n = msgctl(qid,IPC_RMID, 0)) < 0) {
		perror("msgctl");
		exit(0);
    	}
	printf("%d\n",n);
    	printf("555 msg removed\n");
}
