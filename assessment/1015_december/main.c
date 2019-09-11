#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a* createnode();
void traverse(a *head);
a* merge(a *head1,a *head2);
a* break_list(a *head);
int main()
{
	a *head1=NULL,*node=NULL,*p=NULL,*head2=NULL,*int_node=NULL;
	int i,n,j;
	head1=createnode();
	printf("first linked list is\n");
	traverse(head1);
	printf("\n");

	head2=createnode();
	printf("second linked list is\n");
	traverse(head2);
	printf("\n");
	if(head1!=NULL && head2!=NULL)
	{
		head1=merge(head1,head2);
		printf("after merging\n");
		traverse(head1);
		printf("\n");
	}


}
a* createnode()
{
	a *p=NULL,*head=NULL;
	int n,i;
	printf("enter no of nodes to be created\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		a* node=(a *)malloc(sizeof(a));
		printf("enter data to be inserted\n");
		scanf("%d",&node->data);
		node->next=NULL;
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

	return head;
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
a* merge(a *head1,a *head2)
{
	a *p=head1;
	a *q=head2;
	a *n=NULL;
	while(p->next==NULL);
	p=break_list(p);
	while(q->next==NULL)
	q=break_list(q);
	if(p->data<q->data)
	{
		p->next=q;
		return p;
	}
	else
	{
		q->next=p;
		return q;
	}
	return n;
}
a* break_list(a *head)
{
        a *f=head,*s=head;
        while(f->next!=NULL && f!=NULL)
        {
                if(f->next->next==NULL)
                {

                        break;
                }

                f=f->next->next;
                s=s->next;
        }
        s->next==NULL;
        return head;
}

