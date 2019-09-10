/* THis is open system call example */
/* A program that reads a abc file content and writes in to stadard output. */

//#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


main ()
{
	int fd,nread,nwrite,ret;

	char buff[100];

	fd = open ("123",O_RDWR);
	printf ("open system call return value:%d\n",fd);
	if (fd < 0)
	{
		perror("Open FAILS\n");
		exit(0);
	}
//	nread =	read(fd,&buff,6);
//	printf("read ret value:%d\n",nread);
//	nwrite = write(1,&buff,6);
	ret = lseek(fd,1,SEEK_END);
	printf("lseek ret value:%d\n",ret);

	nwrite = write(fd,"Linux",3);
	printf("write ret value:%d\n",nwrite);
	
	close(fd);

}


