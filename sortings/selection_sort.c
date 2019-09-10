#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a* createnode();
void traverse(a *head);
void swap(a *p,a *q);
a* selection_sort(a *head);
a* smallest(a *head);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL;
	int i,n;
	printf("enter number of nodes to be created\n");
	scanf("%d",&n);
	if(n>0)
	{
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

		head=selection_sort(head);
		printf("after sorting linked list is\n");
		traverse(head);
		printf("\n");
	}
	else
		printf("enter number greater than 0\n");
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
a* selection_sort(a *head)
{
	a *p=NULL,*q=NULL;
	p=head;
	while(p!=NULL)
	{
		q=smallest(p);
		if(q!=NULL)
			swap(p,q);
		p=p->next;
	}
	return head;

}
a* smallest(a *head)
{
	a *q=head,*p=head;
	while(p->next!=NULL)
	{
		if(q->data>p->next->data)
			q=p->next;
		p=p->next;
	}
	return q;
}
void swap(a *p,a *q)
{
	int t;
	t=p->data;
	p->data=q->data;
	q->data=t;
}
			
