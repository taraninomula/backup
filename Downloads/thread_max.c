#include<stdio.h> 
#include<pthread.h> 
  
// This function demonstrates the work of thread 
// which is of no use here, So left blank 
void *thread ( void *vargp){     } 
  
int main() 
{ 
    int err = 0, count = 0; 
    pthread_t tid; 
      
    // on success, pthread_create returns 0 and  
    // on Error, it returns error number 
    // So, while loop is iterated until return value is 0 
    while (err == 0) 
    { 
        err = pthread_create (&tid, NULL, thread, NULL); 
        count++; 
    } 
    printf("Maximum number of thread within a Process"
                                   " is : %d\n", count); 
} 
