/* Producer consumer program using pthreads, Semaphores */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


void *producer(void *arg);
void *consumer(void *arg);
char buffer[26];
sem_t empty,full;
pthread_mutex_t mutex;
int counter=0;

int main() {
    int res;
    pthread_t a_thread,b_thread;
    void *thread_result;
    int print_count1 = 0;
   /* Create the full semaphore and initialize to 0 */
   sem_init(&full, 0, 0);

   /* Create the empty semaphore and initialize to BUFFER_SIZE (counting Semaphore) */
   sem_init(&empty, 0, 26);

    res = pthread_create(&a_thread, NULL, producer, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&b_thread, NULL, consumer, NULL);
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
    printf("Thread joined\n");
    exit(EXIT_SUCCESS);
}

void *producer(void *arg) {
    int in = 0,value;
    char ch = 'A';
    while(1)
	{
	//	printf ("producer: counter:%d\n",counter); 
	//	while(counter == 26);
		sem_wait(&empty);
  //	        sem_getvalue(&empty,&value);
  //            printf("producer:empty:  value:%d\n",value);
		buffer[in]=ch;
		in = (in+1)% 26;
		if (in == 0)
		{
		printf("%s\n",buffer);
		ch = 'A';
		}
		else
		ch++;
		sem_post(&full);
  //	        sem_getvalue(&full,&value);
    //          	printf("producer:full: value:%d \n",value);
		//counter++;
	}
	
   pthread_exit("exit");	
}
void *consumer(void *arg) {
    int out = 0, value;
    char buf[26];
    while(1)
	{
		//printf ("consumer: counter:%d\n",counter); 
		//while(counter == 0);
		sem_wait(&full);
  	       // sem_getvalue(&full,&value);
	//	printf("\tconsumer:full:  value:%d\n",value);
		
		buf[out] = buffer[out];
                //printf("\t:%c",buffer[out]);
		out = (out+1)% 26;
		if (out == 0)
		printf("\t%s\n",buf);
		
		sem_post(&empty);
  	       // sem_getvalue(&empty,&value);
                //printf("\tconsumer:empty: value:%d \n",value);
		//counter--;
	}
   pthread_exit("exit");	
}
