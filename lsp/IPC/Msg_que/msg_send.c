
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
    	qid = msgget(KEY, 0666 | IPC_CREAT);
	if (qid < 0) {
		perror("msgget");
		exit(0);
    	}
	message.type = 123;
	strcpy(message.msg, "testing");
	if ((n = msgsnd(qid, &message, 20, 0)) < 0) {
		perror("msgsnd");
		exit(0);
    	}
	printf("%d\n",n);
    	printf("msg sent\n");
}
