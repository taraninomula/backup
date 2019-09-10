#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
	struct student *prev;
}a;
a* createnode();
void traverse(a *head);
a* insert(a *head,int pos);
a* delete(a *head,int pos);
a* reverse(a *head);
void traverse_tail(a *tail);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL,*tail=NULL;
	int n,i,pos,po;
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
			node->prev=p;
			p=p->next;
		}
	}
	tail=p;
	printf("printing from first\n");
	traverse(head);
	printf("\n");

/*	printf("printing from last\n");
	traverse_tail(tail);
	printf("\n");

	printf("enter position of new node to be inserted from 1\n");
	scanf("%d",&pos);
	head=insert(head,pos);
	printf("linked list after inserting is\n");
	traverse(head);
	printf("\n"); 

	printf("enter position of node to be deleted\n");
	scanf("%d",&po);
	head=delete(head,po);
	printf("linked list after deleting is\n");
	traverse(head);
	printf("\n"); */
	
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
void traverse_tail(a *tail)
{
	a *q=tail;
	while(q!=NULL)
	{
		printf("%d\t",q->data);
		q=q->prev;
	}
}
a* insert(a *head,int pos)
{
	a *p=head,*q=NULL;
	int i;
	a *node=(a*)malloc(sizeof(a));
	printf("enter data to be inserted\n");
	scanf("%d",&node->data);
	if(pos==1)
	{
		node->next=p;
		node->prev=NULL;
		p->prev=node;
		head=node;
	}
	else
	{
		for(i=1;i<(pos-1);i++)
			p=p->next;
		q=p->next;
		node->next=p->next;
		node->prev=p;
		q->prev=node;
		p->next=node;
	}
	return head;
}
a* delete(a *head,int pos)
{
	a *p=head,*q=head;
	int i;
	if(pos==1)
	{
		head=p->next;
		free(p);
		p=NULL;
	}
	else
	{
		for(i=1;i<pos;i++)
		{
			q=p;
			p=p->next;
		}
		q->next=p->next;
		if(p->next!=NULL)
			p->next->prev=q;
		free(p);
		p=NULL;
	}
	return head;
}
a* reverse(a *head)
{
	a *n=head,*c=head,*p=head;
	if(head->next!=NULL)
	{
		c=p->next;
		if(c->next!=NULL)
		{
			n=c->next;
			while(c!=NULL)
			{
				c->next=p;
				p->prev=c;
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
			p->prev=c;
			c->prev=NULL;
			p->next=NULL;
			head=c;
		}
	}
	return head;
}


		






	














