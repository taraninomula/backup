#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
int fd,sfd;
char buf[20];

//mkfifo("fifo",S_IRUSR | S_IWUSR | S_IWGRP);
mkfifo("fifo",0660);
while(1)
{
fd=open("fifo",O_RDWR);
if(fd<0)
puts("file not open");
puts("reading data from file");
read(fd,buf,20);
printf("readed data is %s\n",buf);
close(fd);
fd=open("fifo",O_RDWR);
if(fd<0)
puts("file not open");
bzero( buf, 20 );
puts("sending data to file");
scanf("%s",buf);
write(fd,buf,20);
close(fd);
}
}




