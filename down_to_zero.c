#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct node{
	int data;
	struct node *left,*right;
};

int isprime(int n,int *max)
{
	int i;
	int count=0;
	for(i=2;i<=sqrt(n);i++)
	{
		if((n%i)==0)
		{
			*max=n/i;
			count++;
		}
	}
	if(count>0)
		return 0;
	return 1;
}


struct node *newnode(int num)
{
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp->data=num;
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}


struct node *insert_node(struct node *node,int num)
{
	int max=0;
	if(node==NULL)
		node=newnode(num);
	if(num==0)
		return node;
	if(!isprime(num,&max))
	{

		node->left=insert_node(node->left,max);
		node->right=insert_node(node->right,num-1);
	}
	else
		node->left=insert_node(node->left,num-1);
}


int min(int a , int b)
{
	return (a<b ? a:b);
}

int find_minpath(struct node *root)
{
	if(root==NULL)
		return 0;
	if(root->left==NULL && root->right==NULL)
		return 1;
	if(root->left==NULL)
		return find_minpath(root->right) +1;
	if(root->right==NULL)
		return find_minpath(root->left) +1;
	return min(find_minpath(root->left),find_minpath(root->right)) +1 ;
}


int downtozero(int num)
{
	struct node *root=NULL;
	root=insert_node(root,num);
	int min=0;
//	int max=0;
	min=find_minpath(root);
	return min;

}

int main()
{
	int test_cases;
	printf("enter the number of  testcases:  ");
	scanf("%d",&test_cases);
	int num[test_cases];
	printf("\nenter inputs for given number of test cases\n");
	for(int i=0;i<test_cases;i++)
	{
		scanf("%d",&num[i]);
	}
	
	for(int i=0;i<test_cases;i++){
	int count=downtozero(num[i]);
	printf("for number %d needs to move %d back to make zero \n",num[i],count-1);
	}
	return 0;
}


