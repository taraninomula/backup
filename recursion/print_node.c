#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a* createnode();
void traverse(a *head);
int c=1;
a* reverse(a *head);
int print_node(a *p,int n);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL,*q=NULL;
	int i,n,m,res;
	printf("enter number of nodes to be inserted\n");
	scanf("%d",&m);
	for(i=0;i<m;i++)
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
	printf("enter node position to be printed\n");
	scanf("%d",&n);
	q=head;
	if(m>=n && n!=0)
	{
		res=print_node(q,n);
		printf("node %d\n",res);
	}
	else
		printf("enter valid position\n");
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
int print_node(a *p,int n)
{
	if(c==n)
		return p->data;
	else
	{
		c++;
		print_node(p->next,n);
	}
}

			
