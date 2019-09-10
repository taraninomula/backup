#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a* createnode();
void traverse(a *head);
a* alter_ll(a *head);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL,*head1=NULL;
	int i,n;
	printf("enter no of nodes to be inserted\n");
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
	
	head1=alter_ll(head);
	printf("after splitting linked list is\n");
	traverse(head);
	printf("\n");
	traverse(head1);
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
a* alter_ll(a *head)
{
	if(head==NULL)
		return 0;
	a *p=head;
	a *q=head->next;
	a *head1=head->next;
	while(p->next!=NULL && q->next!=NULL)
	{
		if(p->next->next!=NULL)
		{
			p->next=p->next->next;
			p=p->next;
		}
		if(q->next->next!=NULL)
		{
			q->next=q->next->next;
			q=q->next;
		}
	}
	p->next=NULL;
	q->next=NULL;
	return head1;
}



			
