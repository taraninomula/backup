#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
int main()
{
	int pfd[2];
	char *buff[10];
	if(pipe(pfd)==-1)
		perror("pipe\n");
	printf("writing to file descriptor %d\n",pfd[1]);
	write(pfd[1],"tarani",6);
	printf("reading from the file descriptor %d\n",pfd[0]);
	read(pfd[0],buff,6);
	printf("data written into pipe and readed into buffer is %s\n",buff);
}

