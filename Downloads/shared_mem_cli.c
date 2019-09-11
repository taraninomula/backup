#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define KEY 12

int main()
{
  int shmid;
  char *p=NULL;

  shmid=shmget(KEY,512,0);
  if(shmid==-1)
  {
    puts("shared memory accessing error");
    return 0;
  }
  p=shmat(shmid,0,0);
  if(p==(char*)-1)
  {
    puts("invalid address");
    return 0;
  }
  printf("address is : %p\n",p);
  printf("Reading data from shared memory is ");
  puts(p);
  shmdt(p);
  return 0;
}
