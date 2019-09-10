#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char * rm(char *str);
char * rev(char *str);
int main()
{
	char *str=(char *)malloc(sizeof(str));
	char *rev;
	printf("enter string without spaces\n");
	scanf("%s",str);
	rev=rm(str);
	printf("after removing duplicates and reversing %s\n",rev);
}
char * rm(char *str)
{
	char temp[52]={0};
	char *arr=(char *)malloc(sizeof(arr));
	int i,j=0,ind;
	for(i=0;str[i]!='\0';i++)
	{
		if(str[i]>=97 && str[i]<=122)
			ind=str[i]-97;
		if(str[i]>=65 && str[i]<=90)
			ind=str[i]-65+26;
		if(temp[ind]==0)
		{
			arr[j]=str[i];
			j++;
			temp[ind]++;
		}
	}
	arr=rev(arr);
	return arr;
}
char * rev(char *str)
{
	int l=strlen(str)-1;
	int i;
	char rev;
        for(i=0;i<strlen(str)/2;i++)
        {
                rev=str[i];
                str[i]=str[l];
                str[l--]=rev;
        }
	return str;
}



	

