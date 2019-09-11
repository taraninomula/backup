#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node * next;
};
struct node * createnode(struct node *head1)
{
	struct node *new, *temp;
	int i=0,item,j=1;int n;
	temp=head1;
	printf("enter number of elements in linked list\n");
	scanf("%d",&n);
	while(i<n)
	{
		printf("enter element in linked list \n");
		scanf("%d",&item);
		new = (struct node *)malloc(sizeof(struct node));
		new->data = item;
		new->next = NULL; 
		if(head1 == NULL)
		{
			head1=new;

		}
		else if(head1 && (head1->next ==NULL))
		{
			head1->next=new;


		}
		else
		{        temp=head1;
			while(temp->next)
			{
				temp=temp->next;
			}

			temp->next=new;
		}
		i++;
	}
	return head1;
}
void display( struct node * head1)
{
	struct node *temp1;
	temp1=head1;

	if(temp1 == NULL)
	{
		printf("List1 is empty.");
		return ;
	}
	else
	{
		while(temp1 != NULL)
		{
			printf("%d\t", temp1->data); 
			temp1 = temp1->next;                
		}
	}
}
struct node * ascending(struct node * head1, struct node * head2)
{
	struct node * temp=NULL,*h1=NULL,*h2=NULL,*current=NULL;
		if(head1->data <= head2-> data)
		{
			temp=head1;
			head1=head1->next;
		}
		else
		{
			temp=head2;
			head2=head2->next;
		}
		h1=temp;
		while(head1!=NULL && head2 != NULL)
		{
			if(head1->data < head2->data)
			{
				h1->next= head1;
				head1=head1->next;

			}
			else
			{

				h1->next=head2;
				head2=head2->next;
			}
			h1=h1->next;


	}
	if(head1==NULL)
		h1->next= head2;
	else
		h1->next=head1;
	return temp;
}
struct node * descending(struct node * head1, struct node * head2)
{
        struct node * temp=NULL, *h1=NULL;

        if(head1->data >= head2-> data)
                {
                        temp=head1;
                        head1=head1->next;
                }
                else
                {
                        temp=head2;
                        head2=head2->next;
                }
                h1=temp;
                while(head1!=NULL && head2 != NULL)
                {
                        if(head1->data > head2->data)
                        {
                                h1->next= head1;
                                head1=head1->next;

                        }
                        else
                        {

                                h1->next=head2;
                                head2=head2->next;
                        }
                        h1=h1->next;

                }
		if(head1==NULL)
                	h1->next= head2;
        	else
                	h1->next=head1;
	return temp;
}



struct node * Merge(struct node * head1, struct node * head2)
{

	struct node * temp=NULL;
	if(head1==NULL)
		temp=head2;
	if(head2==NULL)
		temp=head1;
	if(head1!=NULL && head2!=NULL)
	{	
	if(head1->data < head1->next->data) 
	{
		temp=ascending(head1,head2);
	}
	else
	{
		temp=descending(head1,head2);
	}
}
	return temp;
}
struct node* reverse(struct node *head)
{
	struct node *n=head,*p=head,*c=head;
	c=c->next;
	if(c->next!=NULL)
	{
		n=c->next;
		while(c!=NULL)
		{
			c->next=p;
			p=c;
			c=n;
			if(n!=NULL)
				n=n->next;
		}
		head->next=NULL;
		head=p;
	}
	else
	{
                c->next=p;
                head=c;
                p->next=NULL;
        }
	return head;
}
int main()
{
	struct node *head1=NULL,*head2=NULL,*head3=NULL;
	head1=createnode(head1);
	head2=createnode(head2);
	printf("list1 elements are\n");
	display(head1);
	printf("\n");
	printf("elements in list2 are\n");
	display(head2);
	printf("\n");
	head3=Merge(head1,head2);
	head3=reverse(head3);
	printf("after merging and reversing list is\n");
	display(head3);
	printf("\n");
}


