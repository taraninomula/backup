#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a* createnode();
void traverse(a *head);
a *remove_duplicates(a *head);
a* reverse(a *head);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL;
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
	
	head=remove_duplicates(head);
	printf("after removing duplicates in  linked list is\n");
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
a *remove_duplicates(a *head)
{
	if(head==NULL)
		return 0;
	if(head->next==NULL)
		return head;
	a *c=head;
	a *n=c->next,*p=head;
	a *temp=NULL;
	while(c!=NULL && n->next!=NULL)
	{
		while(n!=NULL && c->data!=n->data)
		{
			p=n;
			n=n->next;
		}
		if(n==NULL)
		{
			c=c->next;
			n=c->next;
			p=c;
		}
		if( c->data==n->data)
		{
			p->next=n->next;
			temp=n;
			free(temp);
			temp=NULL;
			if(n->next!=NULL)
				n=n->next;
			else
				n=c->next;
		}
		
	}
	if(n->next==NULL)
        {
                if(c->data==n->data)
                {
                        c->next=n->next;
                        temp=n;
                        free(temp);
                }
        }
	return head;
}



			
