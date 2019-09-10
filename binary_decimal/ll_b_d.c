#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int n;
	struct student *next;
}a;
a* createnode();
void traverse(a *head);
int b_to_d(a *head);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL;
	int num,i,dec;
	printf("enter number of nodes in linked list\n");
	scanf("%d",&num);
	printf("enter data in node\n");
	for(i=0;i<num;i++)
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
	printf("data in linked list is\n");
	traverse(head);
	printf("\n");
	dec=b_to_d(head);
	printf("decimal equivalent is %d\n",dec);
	
}
a* createnode()
{
	a *node=(a *)malloc(sizeof(a));
	scanf("%d",&node->n);
	node->next=NULL;
	return node;
}
void traverse(a *head)
{
	a *p=head;
	while(p!=NULL)
	{
		printf("%d\t",p->n);
		p=p->next;
	}
}
int b_to_d(a *head)
{
	a *p=head;
	int sum=0;
	while(p!=NULL)
	{
		sum=(sum<<1)+(p->n);
		p=p->next;
	}
	return sum;
}







