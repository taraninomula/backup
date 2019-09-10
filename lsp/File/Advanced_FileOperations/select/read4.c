#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd1,fd2,retfd;
	char buf[4096];
	int val;

	fd1=open("/dev/input/event1",O_RDONLY);
	if(fd1<0)
		printf("error while open the file event1\n");
	fd2=open("/dev/input/event2",O_RDONLY);
	if(fd2<0)
		printf("error while open the file event2\n");
	
	retfd=read(fd1,buf,4096);
	printf("Read return value - fd1 - keyboard :%d\n",retfd);
	if(retfd<0){
		printf("read is failed\n");
		return -1;
		}

	retfd=read(fd2,buf,4096);
	printf("Read return value of fd2 - Mouse:%d\n",retfd);
	if(retfd<0){
		printf("read is failed\n");
		return -1;
		}
	return 0;
}
		
