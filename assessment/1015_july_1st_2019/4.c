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
	int i,n;
	printf("enter number of nodes in linked list\n");
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
a* reverse(a *head)
{
	a *n=head,*p=head,*c=head;
	c=c->next;
	if(head->next!=NULL)
	{
	if(c->next!=NULL)
	{
		n=c->next;
		while(c!=NULL)
		{
			c->next=p;
			p=c;
			c=n;
			if(n!=NULL)
				n=n->next;
		}
		head->next=NULL;
		head=p;
	}
	else
	{
                c->next=p;
                head=c;
                p->next=NULL;
        }
	}
	return head;
}
			
