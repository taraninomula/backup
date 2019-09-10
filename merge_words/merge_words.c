#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>
FILE *fp_copy,*fp_paste;
pthread_t tid1,tid2;
char word1[100],word2[100];
int mid;
int sig;
int s1=0,s2=0;
sigset_t set;
void write_file();
void *read_word1(void *arg);
void *read_word2(void *arg);
void handler(int sig);
int main(int argc,char *argv[])
{
	int ret1,ret2;
//	mid=pthread_self();
//	int sig;
	sigemptyset(&set);
	sigaddset(&set, SIGALRM);
	sigaddset(&set,SIGUSR1);
	sigaddset(&set, SIGUSR2);
	pthread_sigmask(SIG_BLOCK, &set, NULL);
	mid=pthread_self();
	printf("%s\n",argv[1]);
	fp_copy=fopen(argv[1],"r");
	if(fp_copy==NULL)
		printf("error in opening file\n");
	fp_paste=fopen("paste.txt","a");
	if(fp_paste==NULL)
		printf("error in opening newfile\n");
	//pthread_sigmask(SIG_BLOCK, &set, NULL);
	if(argc==2)
	{
		//	if(fp_copy!=NULL)
		//	{
		ret1=pthread_create(&tid1,NULL,read_word1,NULL);
		if(ret1!=0)
			printf("error in creating thread1\n");
		ret2=pthread_create(&tid2,NULL,read_word2,NULL);
		if(ret2!=0)
			printf("error in creating thread1\n");
		while(s1==0 || s2==0){
		}
		pthread_kill(tid1,SIGUSR1);
		sigwait(&set,&sig);

		while(!feof(fp_copy))
		{
			printf("main\n");
			//sigwait(&set,&sig);
			fprintf(fp_paste,"%s",word1);
			fprintf(fp_paste,"%s",word2);
			printf("main1\n");
			pthread_kill(tid1,SIGUSR1);
			sigwait(&set,&sig);
		}

		ret1=pthread_join(tid1,NULL);
		if(ret1!=0)
			printf("thread1 join failed\n");
		ret2=pthread_join(tid2,NULL);
		if(ret2!=0)
			printf("thread2 join failed\n");
		//pthread_sigmask(SIG_BLOCK, &set, NULL);
		fclose(fp_copy);
		fclose(fp_paste);



		//	}
		//	else
		//		printf("no such file or directory");

	}
	else
		printf("wrong command line arguments\n");
}
void *read_word1(void *arg)
{
//	int sig;
	printf("thread1\n");
	s1=1;
	sigwait(&set,&sig);
	while(!feof(fp_copy))
	{
		fscanf(fp_copy,"%s",word1);
		printf("thread1 reading word %s\n",word1);
		pthread_kill(tid2,SIGUSR2);
		sigwait(&set,&sig);
	}
	//pthread_kill(tid2,SIGUSR2);
	pthread_exit(NULL);
}
void *read_word2(void *arg)
{
//	int sig;
	printf("thread2\n");
	s2=1;
	sigwait(&set,&sig);
	while(!feof(fp_copy))
	{
		fscanf(fp_copy,"%s",word2);
		printf("thread2 reading word %s\n",word2);
		pthread_kill(mid,SIGALRM);
		sigwait(&set,&sig);
	}
	//pthread_kill(mid,SIGALRM);
	pthread_exit(NULL);
}











