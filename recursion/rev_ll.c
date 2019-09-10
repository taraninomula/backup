#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a* createnode();
void traverse(a *head);
//a* head=NULL;
a* reverse(a *head);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL;
	int i;
	for(i=0;i<4;i++)
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

	head=reverse(head);
	printf("after reversing linked list is\n");
	traverse(head);
	printf("\n");
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
	a *p=head;
	while(p!=NULL)
	{
		printf("%d\t",p->data);
		p=p->next;
	}
}
a * reverse(a *head)
{
	a *c=head;
	a *n=c->next;
	a *p=NULL;
	if(c==NULL)
		return NULL;
	if(n==NULL)
		return c;
	c->next=NULL;
	p=reverse(n);
	n->next=c;
	return p;
}
			
