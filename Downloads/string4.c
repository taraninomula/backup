#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ARRAY_SIZE 5 
//int str_len(char buf[]);
void createnode(void);
void printlist(void);
void string_op(void);
struct node
{
unsigned char buf[ARRAY_SIZE];
struct node *nxt;
};
struct node *phead=NULL;
int main(int argc,char *argv[])
{
	char ch;
	do
	{
	createnode();
	printf("do you want to create another node\n");
	scanf(" %c",&ch);
	}
	while(ch=='y');
	string_op();
	printlist();

}

void createnode(void)
{
	struct node *pnew=NULL,*ptrav=NULL,*prnew=NULL;
	pnew=(struct node*)malloc(sizeof(struct node));
	printf("Take i/p from user\n");
	scanf("%s",pnew->buf);
	if(strlen(pnew->buf)>ARRAY_SIZE)
			{
			printf("memory exceeded\n");
			prnew=(struct node*)realloc(pnew,sizeof(struct node));
			}


	printf("pnew->buf is %s\n",pnew->buf);
	pnew->nxt=NULL;
	if(phead==NULL)
	{
	
		phead=pnew;
		printf("phead->buf is %s\n",phead->buf);						
		return;
	}
	
}

void printlist(void)
{
	struct node *ptrav;
	
	if(phead==NULL)
	{

		printf("list is empty");
		return;

	}

	ptrav=phead;
	while(ptrav->nxt!=NULL)
	{
		printf("node data:%s\n",ptrav->buf);
		ptrav=ptrav->nxt;
	}
	printf("node data:%s\n",ptrav->buf);
}
void string_op(void)
{
	struct node *ptrav;
	int i=0;
	//puts("in string_op function");
	if(phead==NULL)
	{

		printf("list is empty");
		return;

	}

	ptrav=phead;
	//printf(" string_op node data:%s\n",ptrav->buf);
	while(ptrav->buf[i]!='\0')
	{
	
		if(i<ARRAY_SIZE)
			ptrav->buf[i]=ptrav->buf[i]+1;
		else
			puts("out of bound");
		
		i++;
	}
	printf("modified string is:%s\n",ptrav->buf);


}



