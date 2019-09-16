#include<stdio.h>
#include<stdlib.h>
int main()
{
	int *arr,n,s=0,i;
	printf("enter number of elements in array\n");
	scanf("%d",&n);
	arr = (int*)malloc(n * sizeof(int));
	printf("enter elements in array\n");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(i=0;i<n;i++)
		s=s+arr[i];
	printf("sum is %d\n",s);
}


