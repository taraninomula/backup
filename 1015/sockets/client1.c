 /*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch[20],ch1[20];

/*  Create a socket for the client.  */

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client1");
        exit(1);
    }
    while(1)
    {

/*  We can now read/write via sockfd.  */

    //write(sockfd, &ch, 1);
 //   printf("from server\n");
    read(sockfd, ch, 20);
    printf("%s\n", ch);
   // printf("to server\n");
    scanf("%s",ch1);
    write(sockfd,ch1,20);
    }
    close(sockfd);
    
}
