#include<stdio.h>
int main()
{
	int n,i,j,t;
	printf("enter number of elements in array\n");
	scanf("%d",&n);
	int arr[n];
	printf("enter elements in array\n");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(i=0,j=n-1;i<j;i++,j--)
	{
		t=arr[i];
		arr[i]=arr[j];
		arr[j]=t;
	}
	printf("after reversing\n");
	for(i=0;i<n;i++)
		printf("%d\t",arr[i]);
	printf("\n");
}


