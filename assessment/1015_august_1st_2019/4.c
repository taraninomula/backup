#include<stdio.h>
#include<string.h>
void fun(char str[100],char sub[10]);

int main()
{
	char str[1000],sub[10];
	int t;
	printf("enter number of test cases\n");
	scanf("%d",&t);
	int i;
	for(i=0;i<t;i++)
	{
		scanf("%s",str);
		scanf("%s",sub);
		fun(str,sub);
	}
}
void fun(char str[100],char sub[10])
{
	if(strstr(str,sub)==NULL)
		printf("NO\n");
	else
		printf("YES\n");
}

