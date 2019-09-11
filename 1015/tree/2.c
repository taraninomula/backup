#include<stdio.h>
#include<stdlib.h>
typedef struct tree
{
	int data;
	struct tree *left;
	struct tree *right;
}a;
a* new_node(int data)
{
	a *node=(a*)malloc(sizeof(a));
	node->data=data;
	node->left=NULL;
	node->right=NULL;
	return node;
}

void inorder(a *node)
{
	if(node==NULL)
		return;
	 
	inorder(node->left);
	printf("%d",node->data);
	inorder(node->right);
}


void preorder(a *node)
{
	if(node==NULL)
		return;
	
	printf("%d",node->data);
	preorder(node->left);
	preorder(node->right);

}

void postorder(a *node)
{
	if(node==NULL)
		return;
	postorder(node->left);
	postorder(node->right);
	printf("%d",node->data);
}

int main()
{
	 a *root=new_node(1);
	 root->left=new_node(2);
	 root->right=new_node(3);
	 root->left->left=new_node(4);
	 root->left->right=new_node(5);
	 printf("inorder is    :");
	 inorder(root);
	 printf("\n");
	 printf("preorder is   :");
	 preorder(root);
	 printf("\n");
	 printf("postorder is  :");
	 postorder(root);
	 printf("\n");
}

