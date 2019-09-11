#include<stdio.h>
#include<stdlib.h>
int main()
{
	char str[100],rev;
	int i,l;
	printf("enter the string\n");
	scanf("%s",str);
	l=strlen(str)-1;
	printf("before reversing %s\n",str);
	for(i=0;i<strlen(str)/2;i++)
	{
		rev=str[i];
		str[i]=str[l];
		str[l--]=rev;
	}
	printf("after reversing %s\n",str);
}


