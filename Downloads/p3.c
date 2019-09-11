#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
void *a1(void *arg);
void *b2(void *arg);
void *c3(void *arg);
void *d4(void *arg);
sem_t s1,s2,s3,s4;
char str[10];
main()
{
int res;
pthread_t a_thread,b_thread,c_thread,d_thread;
void *thread_result;
sem_init(&s1, 0, 1);
sem_init(&s2, 0, 0);
sem_init(&s3, 0, 0);
sem_init(&s4, 0, 0);
//while(1)
{
res = pthread_create(&a_thread, NULL, a1, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
res = pthread_create(&b_thread, NULL, b2, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
res = pthread_create(&c_thread, NULL, c3, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

res = pthread_create(&d_thread, NULL, d4, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
printf("Wait for pthread_join\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(b_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(c_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(d_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
}
}
void *a1(void *arg) {
//sem_post(&full);
while(1)
{
//sem_post(&full);
sem_wait(&s1);
printf("%d\n",1);
//usleep(1);
sem_post(&s2);
//sem_wait(&full);
}
pthread_exit("exit");
}
void *b2(void *arg) {
//sem_post(&full);
while(1)
{
sem_wait(&s2);
printf("%d\n",2);
//usleep(1);
sem_post(&s3);
}
pthread_exit("exit");
}
void *c3(void *arg) {
//sem_post(&full);
while(1)
{
sem_wait(&s3);
printf("%d\n",3);
//usleep(1);
sem_post(&s4);
}
pthread_exit("exit");
}
void *d4(void *arg) {
//sem_post(&full);
while(1)
{
sem_wait(&s4);
printf("%d\n",4);
//usleep(1);
sem_post(&s1);
}
pthread_exit("exit");
}

