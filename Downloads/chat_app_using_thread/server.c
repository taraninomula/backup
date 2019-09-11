#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>    
#include<pthread.h> 

void *connection_recv(void *);
void *connection_send(void *);

#define MAX_SIZE 50

int main(int argc , char *argv[])
{
	int socket_desc ,  c , *new_sock, client_sock;
    	struct sockaddr_in server , client;
    
    	int i = 0;

    	//Create socket
    	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    	if (socket_desc == -1)
    	{
        	printf("Could not create socket");
    	}
    	puts("Socket created");

    	//Prepare the sockaddr_in structure
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_ANY;
    	server.sin_port = htons(1234 );

    	int tr = 1;
    	// kill "Address already in use" error message

    	if (setsockopt(socket_desc,SOL_SOCKET,SO_REUSEADDR,&tr,sizeof(int)) == -1) {
    	perror("setsockopt");
    	exit(1);
    	}


    	//Bind
    	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    	{
        	printf("bind failed\n");
        	//print the error message
       		// perror("bind failed. Error");
        	return 1;
    	}
 

    	puts("bind done");

    	//Listen
    	listen(socket_desc ,3);

    	//Accept and incoming connection
    	puts("Waiting for incoming connections...");
    
    	c = sizeof(struct sockaddr_in);


       while(1)
       {
       		client_sock = accept(socket_desc,(struct sockaddr*)&client,(socklen_t*)&c);           
           	puts("Connection accepted");
           	printf("%d:IP address is: %s\n",i,inet_ntoa(client.sin_addr));
		//printf("port is: %d\n", (int) ntohs(client.sin_port));

  		//printf("Server side(sock desc):%d\n",client_sock);
    

          	pthread_t sniffer_thread[2];
          	new_sock = malloc(sizeof(*new_sock));
          	*new_sock = client_sock;

          	printf("Server side(new sock):%d\n",*new_sock);

       		if( pthread_create( &sniffer_thread[0] , NULL ,  connection_send, (void*) new_sock) < 0)
          	{
               		perror("could not create thread");
               		return 1;
          	}

         	if(pthread_create(&sniffer_thread[1] , NULL, connection_recv,(void*)new_sock) < 0)
         	{
               		perror("could not create thread2");
               		return 1;
         	}
          		//puts("Handler assigned");
    
			//    pthread_join(sniffer_thread[0],NULL);
			//    pthread_join(sniffer_thread[1],NULL);
       
      }
//        close(socket_desc);

      if (client_sock < 0)
      {
      	  perror("accept failed");
          return 1;
      }
     	  return 0;
}

void *connection_send(void *socket_desc)
{
    	//Get the socket descriptor
   	 int sock ; //= *(int*)socket_desc;
    	 int n;

    	printf("sending\n");
    
  	//  printf("sock(send):%d\n",sock);

     	char sendBuff[100];
     	bzero(sendBuff,MAX_SIZE);
      	//fgets(sendBuff,100,stdin);
	printf("before sending msg please enter client fd.\n");
        printf("\n");
     	 while(fgets(sendBuff, 100 , stdin)!=NULL)
     	 {
         	n = strlen(sendBuff);
	        scanf("\n%d",&sock);

          	send(sock,sendBuff,n,0);
           	bzero(sendBuff,MAX_SIZE);
		//     printf("sendBuff:%s\n",sendBuff);
  		//       printf ("Send Return : %ld\n", send(sock,sendBuff,n,0));
      	}
     	close(sock);

      	if(n==0)
      	{
        	puts("Client Disconnected");
      	}
      	else
      	{
        	perror("send failed");
      	}

    	pthread_exit(NULL);
     	pthread_detach(pthread_self());
    	return 0;
}

void *connection_recv(void *socket_desc)
{
    	//Get the socket descriptor
    	int sock = *(int*)socket_desc;
    	int n;

        char client_message[2000];

    	printf("receiving\n");
	//     printf("Server sock(recv):%d\n",sock);

     	bzero(client_message,MAX_SIZE);

      	while((n=recv(sock,client_message,2000,0))>0)
        {
       		// recv(sock,client_message,2000,0);
        	printf("%s\n",client_message);
		memset(client_message,'\0',MAX_SIZE);
        }

      	close(sock);
      	if(n==0)
      	{
        	puts("Client Disconnected");
      	}
      	else
      	{
        	perror("recv failed");
      	}

    	pthread_exit(NULL);
    	pthread_detach(pthread_self());
    	return 0;
}


