#include<stdio.h>
#include<string.h>
int my_strstr(char str[],char sub[]);
char *reverse(char temp[],int i,int l);
int main()
{
	char str[100];
	char sub[100];
	int p;
	printf("enter the string\n");
	scanf("%[^\n]s",str);
	printf("enter the substring\n");
	scanf("%s",sub);
	int l1=strlen(sub);
	p=my_strstr(str,sub);
	reverse(str,p+1,l1);
}
int my_strstr(char str[],char sub[])
{
	int i=0,j=0,c=0,p;
	int l=strlen(sub);
	while(str[i]!='\0')
	{
		while(sub[j]!='\0' && str[i]==sub[j])
		{
			c++;
			i++;
			j++;
			if(c==l)
			{
				p=i;
				printf("word found\n");
				printf("p %d i %d l %d \n",p,i,l);
				j=0;
				i++;
				c=1;
			}
		}
		i++;
	}
	return p;
}
char *reverse(char temp[],int c,int l)
{
	printf("%d\n",c);
	printf("%d\n",l);
	char rev;
	int i,j;
                        for(i=c-l,j=c-1;i<j;i++,j--)
                        {
                                rev=temp[i];
                                temp[i]=temp[j];
                                temp[j]=rev;
                        }
			printf("%s\n",temp);
			return temp;
}
