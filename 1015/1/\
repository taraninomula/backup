#include<stdio.h>
#include<stdlib.h>
typedef struct data
{
int rn;
struct data *next;
}a;
int main()
{
char ch;
int c=0;
a *head=NULL,*node=NULL,*p=NULL;
do
{
a* createnode();
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
printf("do you want to create another node y or n\n");
scanf(" %c",&ch);
c++;
}
while(ch=='y');
printf("out of integer range\n");
void traverse(a *head);
a* afterswap(a *head);
if(c>1)
{
printf("before swapping\n");
traverse(head);
printf("after swapping\n");
head=afterswap(head);
traverse(head);
}
else
printf("minimun 2 nodes should be entered\n");
}
	a* createnode()
	{
	a *node=NULL;
	node=(a*)malloc(sizeof(a));
	printf("enter the data in node\n");
	scanf("%d",&node->rn);
		if(node->rn>=-32768 && node->rn<32767)
		{
		node->next=NULL;
		return node;
		}
		else
		printf("out of integer range\n");
	}
void traverse(a* head)
{
a *p=head;
while(p!=NULL)
{
printf("%d\t",p->rn);
p=p->next;
}
}
a* afterswap(a *head)
{
a *p=head,*n=p->next;
p->next=n->next;
n->next=p;
head=n;
return head;
}


