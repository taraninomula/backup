#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a* createnode();
void traverse(a *head);
void alter_nodes(a *head);
a* insertnode(a *head);
a* deletenode(a *head);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL;
	int i,n;
	printf("enter no of nodes\n");
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

	head=insertnode(head);
	printf("after insertion\n");
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
a* insertnode(a *head)
{
	a *p=head;
	int pos,i,data;
	printf("enter the pos and data\n");
	scanf("%d",&pos);
	a *node=(a *)malloc(sizeof(a));
	scanf("%d",&node->data);
	for(i=1;i<pos-1;i++)
		p=p->next;
	if(p==head)
	{
		node->next=p;
		head=node;
	}
	else if(p->next==NULL)
	{
		p->next=node;
		node->next=NULL;
	}
	else
	{
		node->next=p->next;
		p->next=node;
	}
	return head;
}
a* deletenode(a *head)
{
	a *p=head,*q=head;
	int pos,i;
	printf("enter the position to be deleted\n");
	scanf("%d",&pos);
	if(pos==1)
	{
		p=p->next;
		free(q);
		q=NULL;
		head=p;
	}
		for(i=0;i<pos-1;i++)
		{
			q=p;
			p=p->next;
		}
		if(p==head)
		{
			 p=p->next;
                free(q);
                q=NULL;
                head=p;








			
