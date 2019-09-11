#include<stdio.h>
#include<pthread.h>
void thread1(void *ptr);
void thread2(void *ptr);
void thread3(void *ptr);
void thread4(void *ptr);
int main()
{
  int ret1,ret2,ret3,ret4;
  pthread_t tid1,tid2,tid3,tid4;
  ret1=pthread_create(&tid1,NULL,thread1,NULL);
  pthread_join(tid1,NULL);
  ret2=pthread_create(&tid2,NULL,thread2,NULL);
  pthread_join(tid2,NULL);
  ret3=pthread_create(&tid3,NULL,thread3,NULL);
  pthread_join(tid3,NULL);
  ret4=pthread_create(&tid4,NULL,thread4,NULL);
  pthread_join(tid4,NULL);
  return 0;
}
void thread1(void *ptr)
{
  int i;
  puts("thread1 function created");
  for(i=1;i<=100;i++)
    printf("i is %d\n",i);
}
void thread2(void *ptr)
{
  int i;
  puts("thread2 function created");
  for(i=101;i<=200;i++)
    printf("i is %d\n",i);
}
void thread3(void *ptr)
{
  int i;
  puts("thread3 function created");
  for(i=201;i<=300;i++)
    printf("i is %d\n",i);
}
void thread4(void *ptr)
{
  int i;
  puts("thread4 function created");
  for(i=301;i<=400;i++)
    printf("i is %d\n",i);
}
