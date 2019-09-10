#include<stdio.h>
#include<string.h>
void rm(char *str);
int main()
{
	char str[50];
	printf("enter a string\n");
	scanf("%s",str);
	rm(str);
}
void rm(char *str)
{
	char str1[50],*ptr,rev;
	int i,j=1;
	str1[0]=str[0];
	for(i=1;i<strlen(str);i++)
	{
		ptr=strchr(str1,str[i]);
		if(ptr==NULL)
		{			
			str1[j]=str[i];
			j++;
		}
	}
	printf("%s\n",str1);
	int l=strlen(str1)-1;
	for(i=0;i<strlen(str1)/2;i++)
	{
		rev=str1[i];
		str1[i]=str1[l];
		str1[l--]=rev;
	}
	printf("after reversing %s\n",str1);

}


