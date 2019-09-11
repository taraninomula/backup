//program for simple pipe communication
#include<stdio.h>
#include<string.h>
int main()
{
int fd[2];
char arr[10]={0},buf[10]={0};
if(pipe(fd))
{
perror("pipe open failed");
return;
}
puts("Enter data");
scanf("%s",arr);
write(fd[1],arr,strlen(arr));
read(fd[0],buf,15);
printf("readed data is %s\n",buf);
return 0;
}

