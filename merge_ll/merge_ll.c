#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a* createnode(int n);
a *merge(a *head1,a *temp);
a *find_merge(a *head,a *head1);
void traverse(a *head);
int main()
{
	a *head=NULL,*node=NULL,*p=NULL,*head1=NULL,*int_node=NULL,*node1=NULL,*p1=NULL;
	int i,m1=1,j,m2=9,c;
	for(i=0;i<5;i++)
	{
		node=createnode(m1);
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

		m1++;
	}
	printf("first linked list is\n");
	traverse(head);
	printf("\n");
	for(j=0;j<4;j++)
	{
		node1=createnode(m2);
		if(head1==NULL)
                {
                        head1=node1;
                        p1=node1;
                }
                else
                {
                        p1->next=node1;
                        p1=p1->next;
                }

		m2++;
	}
	printf("second linked list is\n");
	traverse(head1);
	printf("\n");

	printf("enter which case u want to execute \n1.merging at middle node\n2.merging at last node\n3.merging at head\n4.if lists are not merged\n5.If first linked list is not there\n6.If second linked list is not there\n 7.If null is passed in merge");
	scanf("%d",&c);

	switch(c)
	{
		case 1:
			head1=merge(head1,head->next->next);
			printf("after merging\n");
			printf("list 1\n");
			traverse(head);
			printf("\n");
			printf("list2\n");
			traverse(head1);
			int_node=find_merge(head,head1);
			printf("\n");
			printf("merge node= %d\n",int_node->data);
			break;
		       
		case 2:
			head1=merge(head1,head->next->next->next->next);
			printf("after merging\n");
			printf("list 1\n");
			traverse(head);
			printf("\n");
			printf("list2\n");
			traverse(head1);
			int_node=find_merge(head,head1);
			printf("\n");
			printf("merge node= %d\n",int_node->data);
			break;
		       
		case 3:
			head1=merge(head1,head);
			printf("after merging\n");
			printf("list 1\n");
			traverse(head);
			printf("\n");
			printf("list2\n");
			traverse(head1);
			int_node=find_merge(head,head1);
			printf("\n");
			printf("merge node= %d\n",int_node->data);
			break;
		case 4:
			head1=merge(head1,NULL);
			int_node=find_merge(head,head1);
			break;  
		case 5:
			head1=merge(head1,head->next);
                        int_node=find_merge(NULL,head1);
                        printf("\n");
                        break;
		case 6:
			head1=merge(head1,head->next);
                        int_node=find_merge(head,NULL);
                        printf("\n");
                        break;
		case 7:
			head1=merge(NULL,head->next);
			int_node=find_merge(head,head1);
			break;



	}
	
}
a* createnode(int n)
{
	a* node=(a *)malloc(sizeof(a));
	node->data=n;
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
a *merge(a *head1,a *temp)
{
	a *p=head1;
	if(temp!=NULL && head1!=NULL)
	{
		while(p->next!=NULL)
			p=p->next;
		p->next=temp;
	}
	else
		printf("list is not merged\n");
	return head1;
}
a *find_merge(a *head,a *head1)
{
	a *l1=NULL;
	a *l2=NULL;
	if(head!=NULL && head1!=NULL)
	{
	for(l1=head;l1->next!=NULL;l1=l1->next)
	{
		l2=head1;
		while(l2->next!=NULL && l2->next!=l1)
			l2=l2->next;
		if(l2->next==l1)
		break;
	}
	}
	else
		printf("one linked list is not there\n");
	return l1;
}
