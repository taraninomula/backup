#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <linux/input.h>

int main()
{
	int fd1,retfd;
	char buf[4096];
	int val;
	char name[256] = "Unknown";

	fd1=open("/dev/input/event1",O_RDONLY);
	if(fd1<0)
		printf("error while open the file event1\n");
        ioctl(fd1, EVIOCGNAME(sizeof(name)), name);
        printf("Input device name: \"%s\"\n", name);

	return 0;
}
		
