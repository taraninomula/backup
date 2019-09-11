#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char* func1(char s1[]);
typedef struct student
{
	char ch;
	struct student *next;
}a;
a *top=NULL;
void push(char c);
void pop();
int main(int argc,char *argv[])
{
	char temp;
	int i,l;
	a *head=NULL;
	FILE *fp=fopen(argv[1],"r");
	if(fp==NULL)
		printf("error in opening file\n");
	while(!feof(fp))
	{
		temp=getc(fp);
		if(temp=='{' || temp=='[' || temp=='(')
		{
			push(temp);
		}
		if(top!=NULL)
		{
		if((temp=='}' && top->ch=='{')||(temp==']' && top->ch=='[') ||(temp==')' && top->ch=='('))
		{
			pop();
		}
		}
	}
	if(feof(fp))
	{
	if(top==NULL)
		printf("compilation successfull\n");
	else
		printf("compilation failed\n");
	}
	fclose(fp);
	if(fp==NULL)
		printf("error in closing file\n");
}
a* createnode( )
{
	a* node;
	node=(a*)malloc(sizeof(a));
	node->next=NULL;
	return node;
}
void push(char c)
{
	a *node;
	int n;
	node=createnode();
	node->ch=c;
	node->next=top;
	top=node;
}
void pop()
{
	if(top!=NULL)
	{
		a *node,*q;
		q=top;
		top=top->next;
		free(q);
		q=NULL;
	}
}
