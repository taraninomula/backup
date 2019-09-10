#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
	struct student *prev;
}a;
a* createnode();
a* find_tail(a *head);
void make_double(a *head,a* tail);
void print_forward(a *head,a *tail);
void print_backward(a *head,a *tail);
void traverse(a *head);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL,*tail=NULL;
	int i,n;
	printf("enter number of nodes\n");
	scanf("%d",&n);
	if(n)
	{
	for(i=0;i<n;i++)
	{
		node=createnode();
		if(head==NULL)
		{
			head=node;
			p=node;
		}
		else
		{
			p->next=node;
			p=p->next;
		}
	}
	printf("linked list is\n");
	traverse(head);
	printf("\n");

	tail=find_tail(head);
	printf("tail node is %d\n",tail->data);

	//make_double(head,tail);

	printf("head %d\n",head->data);
	printf("tail %d\n",tail->data);
	printf("\n");

	printf("forward list\n");
	print_forward(head,tail);
	printf("\n");

	printf("backward list\n");
	print_backward(head,tail);
	printf("\n");
	}
	else
		printf("nodes are not present\n");


}
a* createnode()
{
	a* node=(a *)malloc(sizeof(a));
	printf("enter data to be inserted\n");
	scanf("%d",&node->data);
	node->next=NULL;
	return node;
}
void traverse(a *head)
{
	if(head!=NULL)
	{
	a *p=head;
	while(p!=NULL)
	{
		printf("%d\t",p->data);
		p=p->next;
	}
	}
	else
		printf("no list\n");
}
a* find_tail(a *head)
{
	a *p=head,*tail=NULL;
	while(p->next!=NULL)
		p=p->next;
	tail=p;
	return tail;
}
void make_double(a *head,a* tail)
{
	a *p=head;
	a *q=p->next;
	p->prev=tail;
	while(p!=tail)
	{
		q->prev=p;
		q=q->next;
		p=p->next;
	}
	tail->next=head;
}
void print_forward(a *head,a *tail)
{
	a *p=head;
	while(p->next!=head)
	{
		printf("%d\t",p->data);
		p=p->next;
	}
	printf("%d\t",p->data);
}
void print_backward(a *head,a *tail)
{
	if(tail->next==head)
	{
		a *q=tail;
		while(q->prev!=tail)
		{
			printf("%d\t",q->data);
			q=q->prev;
		}
		printf("%d\t",q->data);
	}
	else
		printf("double linked list is not available\n");
}













