#include<stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int pid,fd;
  char buf[20];
  pid=fork();
  if(pid)
  {
    puts("Parent process");
    mkfifo("fifo",0660);
    while(1)
    {
      fd=open("fifo",O_RDWR);
      if(fd<0)
        puts("file not open");
      puts("Parent reading data from file");
      read(fd,buf,20);
      printf("Parent readed data is %s\n",buf);
      // puts("Parent sending data to file");
      //scanf("%s",buf);
     // write(fd,buf,20);
    }
    close(fd);
  }
  else
  {
    puts("child process");
    while(1)
    {
      fd=open("fifo",O_RDWR);
      if(fd<0)
        puts("file not open");
      puts("child sending data to file");
      scanf("%s",buf);
      write(fd,buf,20);
      //puts("child reading data from file");
      //read(fd,buf,20);
      //printf("child readed data is %s\n",buf);
      
    }
    close(fd);
  }
  return 0;
}
