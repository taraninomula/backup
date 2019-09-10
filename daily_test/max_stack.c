#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int data;
	struct student *next;
}a;
a *top=NULL,*top1=NULL;
a* createnode( );
void push(int b);
void t_push(int b);
void pop();
void t_pop();
int main()
{
	int i,n,j,b,f=0;
	printf("enter number of choices \n");
	scanf("%d",&n);
	for(j=0;j<n;j++)
	{
		printf("enter your choice 1.push 2.pop 3.max\n");
                scanf("%d",&i);
		if(i==1)
		{
			printf("enter element to push\n");
			scanf("%d",&b);
			if(top==NULL)
			{
				push(b);
				t_push(b);
			}
			else
			{
				push(b);
				if(top1!=NULL)
				{
					if(b>top1->data)
						t_push(b);
				}
			}
		}
		if(i==2)
		{
			if(top->data>top1->data)
			{
				pop();
				t_pop();
			}
			else
				pop();
		}
		if(i==3)
		{
			if(top1!=NULL)
			printf("maximum element is %d\n",top1->data);
		}
	}
}
a* createnode( )
{
	a* node;
	node=(a*)malloc(sizeof(a));
	node->next=NULL;
	return node;
}
void push(int b)
{
	a *node=createnode();
	node->data=b;
	node->next=top;
	top=node;
}
void pop()
{
	a *node,*q;
	if(top==NULL)
		printf("stack1 is empty\n");
	else
	{
		//printf("poped element is %d\n",top->rn);
		q=top;
		top=top->next;
		free(q);
		q=NULL;
	}
}
void t_push(int b)
{
	a *node=createnode();
        node->data=b;
        node->next=top1;
        top1=node;
}
void t_pop()
{
        a *node,*q;
        if(top1==NULL)
                printf("stack2 is empty\n");
        else
        {
                //printf("poped element is %d\n",top1->data);
                q=top1;
                top1=top1->next;
                free(q);
                q=NULL;
        }
}



