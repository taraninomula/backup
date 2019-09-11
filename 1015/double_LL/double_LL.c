#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int rn;
	struct node *next;
	struct node *prev;
}a;
a *swaphead(a *head);
void swapnodes(a *c);
a* createnode();
void traverseb(a *head);
void traversee(a *last);
a* bubblesort(a *head,int n);
int main()
{
	a *head=NULL,*last=NULL,*new_node=NULL;
	int n,i;
	printf("enter number of nodes to be created\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		new_node=createnode();
		if(head==NULL)
		{
			head=new_node;
			last=new_node;
		}
		else
		{
			last->next=new_node;
			new_node->prev=last;
			last=new_node;
		}
	}
	printf("printing linked list from beginning\n");
	traverseb(head);
	printf("\n");
	printf("printing linked list from ending\n");
	traversee(last);
	printf("\n");
	printf("after sorting the list is\n");
	head=bubblesort(head,n);
	traverseb(head);
}
a* createnode()
{
	a *head=NULL,*last=NULL,*new_node=NULL;
	new_node=(a *)malloc(sizeof(a));
	if(new_node==NULL)
		printf("failed to allocate memory for node\n");
	printf("enter data in node\n");
	scanf("%d",&new_node->rn);
	new_node->next=NULL;
	return new_node;
}
void traverseb(a *head)
{
	a *last=NULL,*p=head;
	if(head==NULL)
		printf("list is empty\n");
	while(p!=NULL)
	{
		printf("%d\t",p->rn);
		p=p->next;
	}
}
void traversee(a *last)
{
	a *q=last;
	while(q!=NULL)
	{
		printf("%d\t",q->rn);
		q=q->prev;
	}
}
a* bubblesort(a *head,int n)
{
	a *c=NULL;
	int i=0;
	while(i<n)
	{
		c=head;
		while(c->next!=NULL)
		{
			if((c->rn)>(c->next->rn))
			{
				if(c->prev==NULL){
				head=swaphead(head);
				c=head->next;
				}
				else
				swapnodes(c);
			}
		       else
			c=c->next;
			
		}
		i++;
	}
	return head;
}
a *swaphead(a *head)
{
	a *t=head;
	a *n=t->next;
	a *m=n->next;
	t->next=n->next;
	n->next=t;
	t->prev=n;
	n->prev=NULL;
	if(m)
	m->prev=t;
	head=n;
	return head;
}


void swapnodes(a *c)
{
	a *before=c->prev;
	a *after=c->next;
	a *g=after->next;
	before->next=after;
	c->next=after->next;
	c->prev=after;
	after->next=c;
	after->prev=before;
	if(g)
	g->prev=c;
}
