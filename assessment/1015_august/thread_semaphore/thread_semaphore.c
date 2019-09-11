#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/fcntl.h>
#include<sys/stat.h>
void *thread1(void *ptr);
void *thread2(void *ptr);
void *thread3(void *ptr);
void *thread4(void *ptr);
sem_t *sem1,*sem2,*sem3,*sem4;
int main()
{
	int ret1,ret2,ret3,ret4,j1,j2,j3,j4;
	pthread_t tid1,tid2,tid3,tid4;
	sem1=sem_open("pSem1",O_CREAT|O_EXCL,0666,1);
	sem2=sem_open("pSem2",O_CREAT|O_EXCL,0666,0);
	sem3=sem_open("pSem3",O_CREAT|O_EXCL,0666,0);
	sem4=sem_open("pSem4",O_CREAT|O_EXCL,0666,0);

	sem_unlink("pSem1");
	sem_unlink("pSem2");
	sem_unlink("pSem3");
	sem_unlink("pSem4");
	
	//thread creation
	
	ret1=pthread_create(&tid1,NULL,thread1,NULL);
	if(ret1!=0)
		printf("thread 1 failed\n");
	ret2=pthread_create(&tid2,NULL,thread2,NULL);
	if(ret2!=0)
		printf("thread 2 failed\n");
	ret3=pthread_create(&tid3,NULL,thread3,NULL);
	if(ret3!=0)
		printf("thread 3 failed\n");
	ret4=pthread_create(&tid4,NULL,thread4,NULL);
	if(ret4!=0)
		printf("thread 4 failed\n");


	//joining 
	
	j1=pthread_join(tid1,NULL);
	if(j1!=0)
		printf("join 1 failed\n");
	j2=pthread_join(tid2,NULL);
	if(j2!=0)
		printf("join 2 failed\n");
	j3=pthread_join(tid3,NULL);
	if(j3!=0)
		printf("join 3 failed\n");
	j4=pthread_join(tid4,NULL);
	if(j4!=0)
		printf("join 4 failed\n");
}
void *thread1(void *ptr)
{
	int i=1;
	while(1)
	{
	sem_wait(sem1);
	printf("%d\n",i);
	sem_post(sem2);
	}
	pthread_exit("exit");
}
void *thread2(void *ptr)
{
	int i=2;
	while(1)
	{
	sem_wait(sem2);
	printf("%d\n",i);
	sem_post(sem3);
	}
	pthread_exit("exit");
}
void *thread3(void *ptr)
{
	int i=3;
	while(1)
	{
	sem_wait(sem3);
	printf("%d\n",i);
	sem_post(sem4);
	}
	pthread_exit("exit");
}
void *thread4(void *ptr)
{
	int i=4;
	while(1)
	{
	sem_wait(sem4);
	printf("%d\n",i);
	sem_post(sem1);
	}
	pthread_exit("exit");
}



