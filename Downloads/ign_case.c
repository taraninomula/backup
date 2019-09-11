#include<stdio.h>
int main()
{
	char str1[100],str2[100];
	printf("enter 2 strings\n");
	scanf("%s %s",str1,str2);
	int i,a,f;
	for(i=0;str1[i]!='\0' && str2[i]!='\0';i++)
	{
		if((str1[i]-str2[i]==32) || (str2[i]-str1[i])==32 || (str1[i]==str2[i]))
		{
			printf("yes\n");
			f=0;
		}
		else if(str1[i]!=str2[i])
		{printf("no\n");
			f=1;
			break;
		}
	}

	printf("%d\n",f);
}
