#include<stdio.h>
#include<stdlib.h>
struct node {
				int data;
				struct node *next; 
};

char pop(void);
void  push(int);

struct node * top=NULL;
int main(int argc,char **argv)
{
				FILE *fp; char ch;char c;int flag=0;
				fp=fopen(argv[1],"r");
				if(fp==NULL)
				{
								printf("error\n opening file\n");
								exit(0);
				}
				while((ch=fgetc(fp))!=EOF)
				{
								if((ch=='{')||(ch=='[')||(ch=='('))
												push(ch);

								else if((ch=='}')||(ch==']')||(ch==')'))
								{
												c =	pop();
												if(((c=='{')&&(ch=='}')) ||((c=='(')&&(ch==')'))||((c=='[')&&(ch==']')))
												{

												}
												else
												{
																//	printf("compilation failed\n");
																flag=1; break;
												}
								}
				}
				if((top==NULL) &&(flag==0)) 

								printf("Compilation sucessful\n");
				else 

								printf("compilation failed\n");

				fclose(fp);
				return 0;
}

void push(int data)
{
				struct node *new, *temp;
				int i;

				new = (struct node *)malloc(sizeof(struct node));
				new->data = data;
				new->next = NULL; 
				if(top == NULL)
				{
								top=new;
				}	
				else 
				{ 
								new->next=top;
								top=new;
				}					
}



char pop(void)
{

				int c;
				if(top==NULL)
								return 0;
				c=top->data;
				top=top->next;
				return c;
}
