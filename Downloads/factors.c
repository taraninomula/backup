#include<stdio.h>
int *factor(int n);
int main()
{
	int n,*ptr=NULL,i;
	printf("enter a number\n");
	scanf("%d",&n);
	ptr=factor(n);
	for(i=0;ptr[i]!=0;i++)
		printf("%d\t",ptr[i]);
}
int *factor(int n)
{
	int i,j=0;
	int arr[100];
	int (*ptr)[100];
	for(i=1;i<=n;i++)
	{
		if(n%i==0)
		{
			arr[j]=i;
			j++;
		}
	}
	ptr=&arr;
	return ptr;
}
