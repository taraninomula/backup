/* This examples shows how ls command works in shell

- How to create a new children process is not same as parent process.

 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>


main()
{
pid_t pid;
int ret,status;
char *argv[]={"ps","-eaf"};
pid = fork();
if (pid == 0)
{
	printf("children\n");
	ret = execve("/bin/ps",argv,NULL);
	if(ret == -1)
	perror("execve fails");
	exit(0);
}
else
{
	printf("parent\n");
	wait(&status);
}



}

