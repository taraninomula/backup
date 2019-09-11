#include<stdio.h>
#include<stdlib.h>
typedef struct student
{
int rn;
struct student *next;
}a;
a *top=NULL;
int main()
{

int i;
printf("enter your choice 1.push 2.pop 3.exit\n");
scanf("%d",&i);
a* createnode(int i); 
while(i!=3)
{
if(i==1)
{
void push();
push();
}
if(i==2)
{
void pop();
pop();
}
printf("enter your choice 1.push 2.pop 3.exit\n");
scanf("%d",&i);
}
}
a* createnode(int i)
{
a* node;
node=(a*)malloc(sizeof(a));
node->next=NULL;
return node;
}
void push()
{
a *node;
int n;
node=createnode(1);
printf("enter the no to enter\n");
scanf("%d",&n);
node->rn=n;
node->next=top;
top=node;
//return top;
}
void pop()
{
a *node,*q;
if(top==NULL)
printf("stack is empty\n");
else
{
printf("poped element is %d\n",top->rn);
q=top;
top=top->next;
free(q);
q=NULL;
}
}
