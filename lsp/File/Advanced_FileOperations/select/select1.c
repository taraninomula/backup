#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	fd_set read_fileset;
	int fd1,fd2, retfd;
	int buf;
	int val,ret;
	char buff[4099];
	
	fd1=open("/dev/input/event1",O_RDONLY);
	if(fd1<0)
		printf("error while open the file event1\n");
	fd2=open("/dev/input/event2",O_RDONLY);
	if(fd2<0)
		printf("error while open the file event2\n");
	
	/* initially makes as zero files */
	FD_ZERO(&read_fileset);

	while(1){
		/* add our file discriptors */
		FD_SET(fd1,&read_fileset);
		FD_SET(fd2,&read_fileset);
		retfd=select(FD_SETSIZE,&read_fileset,NULL,NULL,0);
		printf ("retfd:%d\n",retfd);
		if(retfd<0){
			printf("select is failed\n");
			return -1;
		}
		/* Keyboard data event0  */
		if(FD_ISSET(fd1,&read_fileset)){
			printf("data is available on keyboard event0\n");
			ret = read(fd1,&buff,4010);
			printf ("ret:%d\n",ret);
		}
		/* Mouse data event1  */
		if(FD_ISSET(fd2,&read_fileset)){
			printf("data is available on mouse event1\n");
			ret = read(fd2,&buff,4096);
			printf ("ret:%d\n",ret);
		}
	}
	return 0;
}
		
