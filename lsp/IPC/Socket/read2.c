#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

main()
{
char buffer[30];
int ret,nread;
fd_set inputs;

	FD_ZERO(&inputs);
	FD_SET(0,&inputs);
 
	ret = select(FD_SETSIZE, &inputs, (fd_set *)0, (fd_set *)0, 0);
        printf ("ret:%d\n", ret);

	ioctl(0,FIONREAD,nread);	
	ret = read(0,buffer,nread);
	printf("ret:%d\n",ret);
}
