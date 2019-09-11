#include<stdio.h>
#include<stdlib.h>
typedef struct data
{
int rn;
struct data *next;
}a;
int c=1;
a *front=NULL,*rear=NULL,*head=NULL,*node=NULL,*q=NULL;
int main()
{
int b;
printf("enter your choice 1.enqueue 2.dequeue 3.exit\n");
scanf("%d",&b);
a* createnode();
while(b!=3)
{
if(b==1)
{
void enqueue();
enqueue();
c++;
}
if(b==2)
{
void dequeue();
dequeue();
c--;
}
printf("enter your choice 1.enqueue 2.dequeue 3.exit\n");
scanf("%d",&b);
}
}
a* createnode()
{
node=(a*)malloc(sizeof(a));
node->next=NULL;
return node;
}
void enqueue()
{
int n;
if(c<=5)
{
	node=createnode();
	printf("enter the no\n");
	scanf("%d",&n);
	node->rn=n;
	if(head==NULL)
	{
		head=node;
		node->next=NULL;
		front=rear=node;
	}
	else
	{ 
		rear->next=node;
		rear=rear->next;
		rear->next=front;
	}
}
else
printf("queue is full\n");
}
void dequeue()
{
if(front == NULL)
{
	printf("queue is empty\n");
	return;
}
if(front==rear)
{
	printf("dequeued data is %d:\n",front->rn);
	free(front);
	front=NULL;
	rear=NULL;
}
else
{
printf("dequeued data is %d:\n",front->rn);
q=front;
front=front->next;
rear->next=front;
free(q);
q=NULL;
}
}
