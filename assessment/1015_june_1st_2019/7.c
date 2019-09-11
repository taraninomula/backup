#include<stdio.h>
int main()
{
	int s,i,j=0;
	printf("enter the number of elements to be created\n");
	scanf("%d",&s);
	int arr[s];
	printf("enter the elements\n");
	for(i=0;i<s;i++)
		scanf("%d",&arr[i]);
	int rev[s];
	for(i=s-1;i>=0;i--)
	{
		rev[j]=arr[i];
		j++;
	}
	printf("after reversing elements are\n");
	for(i=0;i<s;i++)
		printf("%d\t",rev[i]);
	printf("\n");

}
