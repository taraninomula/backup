

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>

#define KEY	555	

struct mesg{
  long int type;
    char msg[20];
   };

main()
{  
	struct  mesg message;
	int qid,n;
	qid=msgget(555,0666);
	if(qid<0)
	{ 
		perror("msgget");
		exit(0);
        }			// Any first message in the msg queue
	if((n=msgrcv(qid,&message,20,0,0))<0)
  	{ 	
		perror("msgrcv");
		exit(0);
    	}
	printf("msg is:%s\n",message.msg);
	printf("msg typ is %d\n",message.type);
}
