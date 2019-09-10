#include<stdio.h>
#include <pthread.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<signal.h>
sigset_t set;
FILE *fp_copy,*fp_paste;
char word1[100],word2[100];
void *thread_result;
pthread_t tid1,tid2, mid;
void *read_word1(void *arg);
void *read_word2(void *arg);
int main(int argc, char *argv[])
{
	int sig,ret;
	mid=pthread_self();
	
	sigemptyset(&set);
	sigaddset(&set,10);
	sigaddset(&set,12);
	sigaddset(&set,34);
	if(argc!=3)
		printf("Enter file name and word properly\n");
	fp_copy=fopen(argv[1],"r");
	fp_paste=fopen(argv[2],"a");
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	ret = pthread_create(&tid1, NULL, &read_word1, NULL);
	if (ret != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);}
	ret = pthread_create(&tid2, NULL, &read_word2, NULL);
	if (ret != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);}
	pthread_kill(tid1,34);
	while(!feof(fp_copy)&&tid1)
	{
		sigwait(&set,&sig);
		fprintf(fp_paste,"%s",word1);
		fprintf(fp_paste,"%s"," ");
		fprintf(fp_paste,"%s",word2);
		fprintf(fp_paste,"%s"," ");
		pthread_kill(tid1,34);
	}
	printf("main\n");
	ret=pthread_join(tid1, &thread_result);
	if (ret != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	ret=pthread_join(tid2, &thread_result);
	if (ret != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);}
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	fclose(fp_copy);
	fclose(fp_paste);


}
void *read_word1(void *arg)
{
	int sig;
	sigwait(&set,&sig);
	while(tid2 && (fscanf(fp_copy,"%s",word1)!=EOF))
	{			
		//fscanf(fp_copy,"%s",word1);
		pthread_kill(tid2,12);
		sigwait(&set,&sig);
		memset(word1,'\0',sizeof(word1));
	}	
	pthread_kill(tid2,12);
	pthread_exit(0);		
}
void *read_word2(void *arg)
{
	int sig;
	sigwait(&set,&sig);
	while(mid &&(fscanf(fp_copy,"%s",word2)!=EOF))
	{
		//fscanf(fp_copy,"%s",word2);
		pthread_kill(mid,34);
		sigwait(&set,&sig);
		memset(word2,'\0',sizeof(word2));
	}
	pthread_kill(mid,34);
	pthread_exit(0);
}
