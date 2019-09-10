#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a* createnode();
void traverse(a *head);
a* reverse(a *head);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL;
	int n,i,pos,po,k;
	printf("enter number of nodes to be created in linked list\n");
	scanf("%d",&n);
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
	printf("data in linked list is\n");
	traverse(head);
	printf("\n");

	printf("after reversing list is\n");
	if(head!=NULL)
		head=reverse(head);
	traverse(head);
	printf("\n");

}
a* createnode()
{
	a *node=(a *)malloc(sizeof(a));
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
	
a* reverse(a *head)
{
	a *c=NULL,*p=NULL,*n=NULL;
	c=head;
	while(c!=NULL)
	{
		n=c->next;
		c->next=p;
		p=c;
		c=n;
	}
	return p;
}
	














