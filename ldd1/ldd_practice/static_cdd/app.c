#include<stdio.h>
#include <stdlib.h>
#include <fcntl.h>
main()
{
int fd;
char buf[100];
printf("enter string\n");
scanf("%[^\n]s",buf);
fd=open("/dev/my_char",O_RDWR);
if(fd<0){
    printf("file open error\n");
    return;
  }
write(fd,buf,100);
read(fd,buf,100);
printf("%s\n",buf);
}
