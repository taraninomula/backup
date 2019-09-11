#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


main()
{

int fd,ret;
char buff[10];

	fd = open("/dev/memory",O_RDWR);
	if (fd < 0)
	perror("open FAILS\n");
	
	ret = write(fd,"123",3);
	printf("write return value:%d\n",ret);
	
	ret = read(fd,buff,100);
	printf("read return value:%d buff[0]:%s \n",ret,buff);

	close(fd);
}
