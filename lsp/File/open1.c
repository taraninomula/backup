/* THis is open system call example */
/* A program that reads a abc file content and writes in to stadard output. */

//#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


main ()
{
	int fd,nread,nwrite;

	char buff[100];

	fd = open ("abc",O_RDONLY);
	printf ("open system call return value:%d\n",fd);
	if (fd < 0)
	{
		perror("Open FAILS\n");
		exit(0);
	}

		
	while (0 != read(fd,&buff,7))
	{
	nwrite = write(1,&buff,7);
	}

	close(fd);

}


