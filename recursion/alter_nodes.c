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
	
	printf("alternative nodes are\n");
	alter_nodes(head);
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
void alter_nodes(a *p)
{
	if(p==NULL)
		return;
	printf("%d\t",p->data);
	if(p->next!=NULL)
		alter_nodes(p->next->next);

}

			
