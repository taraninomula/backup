#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <linux/input.h>

int main()
{
	int i,rd,fd1,retfd;
	char buf[4096];
	int val;
	char name[256] = "Unknown";
	struct input_event ev[64];
	fd1=open("/dev/input/event2",O_RDONLY);
	if(fd1<0)
		printf("error while open the file event1\n");
        ioctl(fd1, EVIOCGNAME(sizeof(name)), name);
        printf("Input device name: \"%s\"\n", name);

while(1)
{
	rd=read(fd1, ev, sizeof(struct input_event) * 64);
        if (rd < (int) sizeof(struct input_event)) {
                        printf("yyy\n");
                        perror("\nevtest: error reading");
                        return 1;
         }

        for (i = 0; i < rd / sizeof(struct input_event); i++)
	printf("Event: time %ld.%06ld, type %d , code %d , value %d\n",ev[i].time.tv_sec, ev[i].time.tv_usec, ev[i].type,ev[i].code, ev[i].value);

}
	return 0;
}
		
