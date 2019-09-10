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
void delete(a *node);
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
	node1=head;

	printf("enter node position to be deletd\n");
	scanf("%d",&pos);
	for(i=1;i<pos;i++)
		node1=node1->next;
	delete(node1);
	printf("after deleting linked list is\n");
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
void delete(a *node)
{
	a *temp=NULL;
	if(node->next==NULL)
	{
		temp=node;
		free(temp);
		temp=NULL;
	}
	else
	{
		temp=node->next;
		node->data=temp->data;
		node->next=temp->next;
		free(temp);
		temp=NULL;
	}
}





			
