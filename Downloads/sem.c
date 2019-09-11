#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
void *producer(void *arg);
void *consumer(void *arg);
sem_t empty,full;
char str[10];
main()
{
//sem_t empty,full;
pthread_t a_thread,b_thread;
void *thread_result;
sem_init(&full, 0, 0);
//sem_init(&empty, 0, 26);
//pthread_t a_thread,b_thread;
pthread_create(&a_thread, NULL, producer, NULL);
pthread_create(&b_thread, NULL, consumer, NULL);
pthread_join(a_thread, &thread_result);
pthread_join(b_thread, &thread_result);
}
void *producer(void *arg) {
while(1)
{
sem_wait(&full);
printf("reading %s\n",str);
//sem_post(&full);
//printf("%d\n",full);
}
pthread_exit("exit");
}
void *consumer(void *arg) {
while(1)
{
printf("consumer is sending\n");
scanf("%s",str);
sem_post(&full);
/*sem_wait(&empty);
printf("%d",empty);
sem_post(&full);
printf("%d\n",full);*/
}
pthread_exit("exit");
}
