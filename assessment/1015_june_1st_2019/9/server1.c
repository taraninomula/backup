

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;


    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);



    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);



    listen(server_sockfd, 5);
    //while(1) {
        char ch[20],ch1[20];
	//printf("to client\n");
//	scanf("%s",ch);

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);

	while(1)
	{
	scanf("%s",ch);
        write(client_sockfd, ch, 20);
	//printf("from client\n");
	read(client_sockfd,ch1, 20);
	printf("%s\n",ch1);
	}
	close(client_sockfd);
   
}

