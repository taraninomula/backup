#include<stdio.h>
#include<string.h>
int main()
{
	char s[1000],i,j=0;
	printf("enter a sentence\n");
	scanf("%[^\n]s",s);
	char temp[100];
	printf("%c\n",s[2]);
//	for(i=0;s[i]!='\0';i++)
//		printf("%c",s[i]);
	
	for(i=0;s[i]!='\0';i++)
	{
		if(s[i]==' ')
		{
			printf("%s\n",temp);
			memset(temp,0,sizeof(temp));
			j=0;
		}
		temp[j]=s[i];
		j++;
	}
}
