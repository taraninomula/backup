/* Producer consumer program using pthreads, Semaphores and mutex*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>


void *producer1(void *arg);
void *producer2(void *arg);
void *consumer(void *arg);
char buffer[5];
sem_t empty,full;
pthread_mutex_t prod,cons;

int main() {
    int res,i;
    pthread_t a_thread,b_thread,c_thread;
    void *thread_result;
    int print_count1 = 0;
   /* Create the full semaphore and initialize to 0 */
   sem_init(&full, 0, 0);

   /* Create the empty semaphore and initialize to BUFFER_SIZE (counting Semaphore) */
   sem_init(&empty, 0, 5);

//for (i=0; i<2; i++)
//{
    res = pthread_create(&a_thread, NULL, producer1, NULL );
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&b_thread, NULL, producer2, NULL );
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
//}
    res = pthread_create(&c_thread, NULL, consumer, NULL);
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

void *producer1(void *arg) {
    int in = 0,value;
    char ch='A';
    while(1)
	{
	//	printf ("producer: counter:%d\n",counter); 
		//while(counter == 5);
		sem_wait(&empty);
  	        //sem_getvalue(&empty,&value);
                //printf("producer:empty:  value:%d\n",value);
	      /* acquire the mutex lock */

      		pthread_mutex_lock(&prod);
		buffer[in]=ch;
		in = (in+1)% 5;
		ch++;
		if (in == 0)
		{
			ch='A';
			printf("p1:%s\n",buffer);
		}
	      /* release the mutex lock */
      		pthread_mutex_unlock(&prod);

		sem_post(&full);
  	        //sem_getvalue(&full,&value);
                //printf("producer:full: value:%d\n",value);
		//counter++;
	}
	
   pthread_exit("exit");	
}

void *producer2(void *arg) {
    int in = 0,value;
    char ch='a';
    while(1)
	{
	//	printf ("producer: counter:%d\n",counter); 
		//while(counter == 5);
		sem_wait(&empty);
  	        //sem_getvalue(&empty,&value);
                //printf("producer:empty:  value:%d\n",value);
	      /* acquire the mutex lock */

      		pthread_mutex_lock(&prod);
		buffer[in]=ch;
		in = (in+1)% 5;
		ch++;
		if (in == 0)
		{
			ch='a';
			printf("p2:%s\n",buffer);
		}
	      /* release the mutex lock */
      		pthread_mutex_unlock(&prod);

		sem_post(&full);
  	        //sem_getvalue(&full,&value);
                //printf("producer:full: value:%d\n",value);
		//counter++;
	}
	
   pthread_exit("exit");
}	
void *consumer(void *arg)  {
    int out = 0, value;
    char temp[5];
    while(1)
	{
		//printf ("consumer: counter:%d\n",counter); 
		//while(counter == 0);
		sem_wait(&full);
  	        //sem_getvalue(&full,&value);
                //printf("\tconsumer:full:  value:%d\n",value);
	      /* acquire the mutex lock */
      		pthread_mutex_lock(&prod);
		temp[out] = buffer[out];
		out = (out+1)% 5;
	      /* release the mutex lock */
		if (out == 0)
		{
		printf("\t%s\n",temp);
		}
      		pthread_mutex_unlock(&prod);
		sem_post(&empty);
  	       // sem_getvalue(&empty,&value);
                //printf("\tconsumer:empty: value:%d\n",value);
		//counter--;
	}
   pthread_exit("exit");	
}
