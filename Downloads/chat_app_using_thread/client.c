#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_SIZE 50

void *connect_send(void *sock_des)
{
	int sock = *(int*)sock_des;
    	int n = 0;

    	printf("sending\n");

	//    printf("sock(send):%d\n",sock);
    
     	char sendBuff[100];

     	bzero(sendBuff,MAX_SIZE);

     	while(fgets(sendBuff, 100 , stdin)!=NULL)
     	{
    		// printf("sendBuff:%s\n",sendBuff);
     		n = strlen(sendBuff);
     		send(sock,sendBuff,n,0);
     		bzero(sendBuff,MAX_SIZE);
     		//printf ("Send Returns : %ld\n", send(sock,sendBuff,n,0));
     	}
     

      	close(sock);
      	pthread_exit(NULL);
       	pthread_detach(pthread_self());
      	return 0;
}


void *connect_recv(void *sock_des)
{
 	int sock = *(int*)sock_des;
    	int n = 0;

        char server_message[2000];

        printf("receiving\n");

	//    printf("Clientsock(recv):%d\n",sock);
      	bzero(server_message,MAX_SIZE);

        while((n=recv(sock,server_message,2000,0))>0)
        {
        	 printf("%s\n",server_message);
    		 bzero(server_message,MAX_SIZE);
        }
    
     	bzero(server_message,MAX_SIZE);  

     	close(sock);
      	pthread_detach(pthread_self());
    	pthread_exit(NULL);
    	return 0;
}

int main()
{
	int sock_desc,*new_sock;
    	struct sockaddr_in serv_addr;
	//    char sbuff[MAX_SIZE],rbuff[MAX_SIZE];

    	if((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("Failed creating socket\n");

    	bzero((char *) &serv_addr, sizeof (serv_addr));

    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    	serv_addr.sin_port = htons(1234);

    	if (connect(sock_desc, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        printf("Failed to connect to server\n");
        return -1;
    	}

  	//  printf("client side(sock desc):%d\n",sock_desc);

    	printf("Connected successfully\n");

    	pthread_t thread[2];
    	new_sock = malloc(sizeof(*new_sock));
    	*new_sock = sock_desc;

    	//printf("client side(new sock):%d\n",*new_sock);

    	if( (pthread_create(&thread[0], NULL,connect_send,(void*)new_sock)) != 0 )
       	   	 printf("client : Failed to create thread\n");

    	if( pthread_create(&thread[1], NULL,connect_recv,(void*)new_sock) != 0 )
     	         printf("client : Failed to create thread\n");    
    
    	pthread_join(thread[0],NULL);
    	pthread_join(thread[1],NULL);

    	close(sock_desc);
    	return 0;
   
}

