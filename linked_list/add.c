//delete a node with single pointer

#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a* createnode();
void traverse(a *head);
a* add(a *node,int p);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL,*node1=NULL;
	int i,n,pos;
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

	printf("after adding\n");
	head=add(head,5);
	traverse(head);

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
a* add(a *head,int pos)
{
	int i=1;
	a *p=head;
	a *node=(a*)malloc(sizeof(a));
	printf("enter data to enter\n");
	scanf("%d",&node->data);
	if(pos==1)
	{
		node->next=head;
		head=node;
	}
	else
	{
		while(i!=pos-1)
		{
			i++;
			p=p->next;
		}
		node->next=p->next;
		p->next=node;
	}
	return head;
}











			
