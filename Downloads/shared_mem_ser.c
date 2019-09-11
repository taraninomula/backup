//http://tuxthink.blogspot.com/2012/03/inter-process-communication-using_19.html
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define KEY 12
#define SIZE 512
int main()
{
  int shmid;
  char *addr=NULL;
  shmid=shmget(KEY,SIZE,0777|IPC_CREAT);
  if(shmid==-1)
  {
    puts("shared memory is not created");
    return 0;
  }
  addr=shmat(shmid,0,0);
  printf("address is : %p\n",addr);
  if(addr==(char*)-1)
  {
    puts("invalid address");
    return 0;
  }
  puts("writting data to shared memory");
  scanf("%s",addr);
  puts(addr);
  return 0;
}






