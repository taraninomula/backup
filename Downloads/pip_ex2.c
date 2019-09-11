//program for pipe communication between child process and parent process 
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
int fd[2];
char arr[20]="IPC creation",buf[10]={0};  //arr[20]="IPC creation"  arr[20]
if(pipe(fd))
{
perror("pipe open failed");
return 0;
}
puts("creating new process");
if(fork())
{
puts("child process created successfully");
//puts("Enter data");
//scanf("%s",arr);
write(fd[1],arr,15);
exit(0);
}
else
{
puts("parent process created successfully");
read(fd[0],buf,15);
printf("readed data is %s\n",buf);
}
return 0;
}

