#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>

#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	fd_set read_fileset;
	int fd2,fd3, retfd;
	int buf;
	int val;
	fd2=open("/dev/input/event1",O_RDONLY);
	if(fd2<0)
		printf("error while open the file event1\n");
	fd3=open("/dev/input/event2",O_RDONLY);
	if(fd3<0)
		printf("error while open the file event2\n");
	
	/* initially makes as zero files */
	FD_ZERO(&read_fileset);

	/* add our file discriptors */
	FD_SET(fd2,&read_fileset);
	FD_SET(fd3,&read_fileset);

	retfd=select(FD_SETSIZE,&read_fileset,NULL,NULL,0);
	if(retfd<0){
		printf("select is failed\n");
		return -1;
		}
	/* Touch screen data event0  */
	if(FD_ISSET(fd2,&read_fileset))
		printf("data is available on  power button event1\n");
	if(FD_ISSET(fd3,&read_fileset))
		printf("data is available on mouse event2\n");

	return 0;
}
		
