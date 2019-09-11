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
a* last_node(a *node);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL,*last=NULL;
	int i;
	for(i=0;i<5;i++)
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

	/*head=reverse(head);
	printf("after reversing linked list is\n");
	traverse(head);
	printf("\n");*/
	last=last_node(head);
	printf("last node is %d\n",last->data);
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
	return head;
}
a* last_node(a *node)
{
	if(node->next==NULL)
		return node;
	last_node(node->next);
}
			
