/* list1= 10->20->30->40->50
	list2= 15-> 16-> 25-> 100

output ascending =  10->15->16->20-> 25-> 30-> 40-> 100



list1= 90->80->70->60->40
list2= 50->40->30->20->-10
output descending = 90->80->70->60->50->40->30->20->10
*/


#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node * next;
};
struct node * Inputlist1(struct node *head1)
{
	struct node *new, *temp;
	int i=0,item,j=1;int n;
	temp=head1;
	printf("enter how many nodes u want:\n");
	scanf("%d",&n);
	while(i<n)
	{
		printf("entr element for list \n");
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
	}//while
	return head1;
}


void display( struct node * head1)
{
	struct node *temp1,*temp2;
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
			printf("%d->", temp1->data); 
			temp1 = temp1->next;                
		}
	}
}

struct node * ascending(struct node * head1, struct node * head2)
{
	struct node * temp=NULL,*h1=NULL,*h2=NULL,*current=NULL;
	if(head1==NULL)
		temp=head2;
	 if(head2==NULL)
		temp=head1;
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

	if(head1==NULL)
		temp=head2;
	 if(head2==NULL)
		temp=head1;
	
	
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

	printf("in merge\n");struct node * temp=NULL;
	if(head1==NULL || head2==NULL)
	{
		printf("heads are null\n;");
		return NULL;
	}
	if(head1->data < head1->next->data) //aescending
	{
		temp=ascending(head1,head2);
	}
	else
	{
		temp=descending(head1,head2); // descending
	}
	return temp;
}



int main()
{
	struct node * head1=NULL;
	struct node * head2=NULL;
	struct node * head3=NULL;
	head1=Inputlist1(head1);
	display(head1);
	head2=Inputlist1(head2);
	display(head2);
	head3=Merge(head1,head2);
	display(head3);
}


