
#include<stdio.h>
#include<stdlib.h>
#include"1015_test.h"
struct node *root=NULL;
int main()
{
	struct node *p=NULL,*new_node=NULL;
	int i;
	for(i=0;i<10;i++)
	{
		new_node=(node *)malloc(sizeof(struct node));
		printf("enter data for new node\n");
		if(new_node==NULL)
			printf("malloc failed\n");
		scanf("%d",&new_node->data);
		if(new_node->data<=-32768 && new_node->data>32767)
			printf("enter data in range of integer\n");
		new_node->ptr_next=NULL;
		new_node->ptr_next_next=NULL;
		insert_node(new_node);
	}

	printf("printing nodes after inserting\n");
	print_LL(root);
	printf("\n");

	printf("after swapping\n");
	swap_node(root->ptr_next);
	print_LL(root);
	printf("\n");

	printf("after deleting\n");
	printf("%d\n",root->ptr_next_next->data);
	delete_node(root);
	print_LL(root);
	printf("\n");
}
void insert_node(node *ptr)
{
	node *p=NULL;
	if(root==NULL)
	{
		root=ptr;
		return ;
	}
		p=root;
	
	while(p->ptr_next!=NULL)
	{
		if(p->ptr_next->ptr_next!=NULL)
			p->ptr_next_next=p->ptr_next->ptr_next;
		p=p->ptr_next;
	}
	p->ptr_next=ptr;
	
}
void print_LL(node *root)
{
	node *q=root;
	if(root==NULL)
		printf("list is empty\n");
	while(q!=NULL)
	{
		printf("%d\t",q->data);
		q=q->ptr_next;
	}
}
void delete_node(node *ptr)
{
	node *d=root,*temp=ptr;
	if(ptr==root)
	{
		root=ptr->ptr_next;
		free(ptr);
		ptr=NULL;
	}
	else
	{
		while(d->ptr_next!=NULL)
		{
			if(d->ptr_next==ptr)
			{
				if(ptr->ptr_next==NULL)
				{
					d->ptr_next=NULL;
					//d->ptr_next_next=ptr->ptr_next_next;
					//d->ptr_next_next=NULL;
					free(temp);
					temp=NULL;
				}
				else
				{
				d->ptr_next=ptr->ptr_next;
				d->ptr_next_next=ptr->ptr_next_next;
				free(ptr);
				ptr=NULL;
				}
			}
			d=d->ptr_next;
		}
	}

}
void swap_node(node *ptr)
{
	node *t=root,*p1=ptr->ptr_next;
	if(ptr==root)
	{
	node *n=ptr->ptr_next;
	node *s=ptr->ptr_next_next;
	ptr->ptr_next=s;
	ptr->ptr_next_next=s->ptr_next;
	n->ptr_next=ptr;
	n->ptr_next_next=root->ptr_next;
	root=n;
	}
	else
	{
		while(t->ptr_next!=ptr)
			t=t->ptr_next;
		t->ptr_next=p1;
		t->ptr_next_next=ptr;
		t->ptr_next->ptr_next=ptr;
		//ptr->ptr_next=p1;
		//ptr->ptr_next_next=p1->ptr_next;
		ptr->ptr_next=ptr->ptr_next_next;
		ptr->ptr_next_next=ptr->ptr_next->ptr_next;
	}
}


	




	







