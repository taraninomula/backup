#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
	int a,b,ssum;
	struct student *next;
}a;
void createnode();
a *search(int sum);
a *head=NULL,*p=NULL;
int main()
{
	int i,j,n,sum,f=0;
	a *q=NULL;
	printf("enter no of elements in array\n");
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(i=0;i<n;i++)
		for(j=i+1;j<n;j++)
		{
			sum=arr[i]+arr[j];
			q=search(sum);
			if(q)
			{
				printf("%d,%d and %d,%d\n",arr[i],arr[j],q->a,q->b);
				f=1;
			}
			else
				createnode(sum,arr[i],arr[j]);
		}
	if(f==0)
		printf("no pairs found\n");

}
void createnode(int s,int i,int j)
{
	a* node=(a *)malloc(sizeof(a));
	node->ssum=s;
	node->a=i;
	node->b=j;
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
a *search(int sum)
{
	a *p=head,*q=NULL;
	while(p!=NULL)
	{
		if(p->ssum==sum)
			q=p;
		p=p->next;
	}
	return q;
}

			
