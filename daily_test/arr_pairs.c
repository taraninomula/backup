#include<stdio.h>
int find_max(int arr[],int n);
int arr_pairs(int arr[],int n,int max);
int main()
{
	int n,i,j,max,c;
	printf("enter size of array\n");
	scanf("%d",&n);
	int arr[n];
	printf("enter elements of array\n");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	max=find_max(arr,n);
	printf("max is %d\n",max);
	c=arr_pairs(arr,n,max);
	printf("number of array pairs are %d\n",c);
}
int find_max(int arr[],int n)
{
	int max,i;
	max=arr[0];
	for(i=0;i<n;i++)
	{
		if(max<arr[i])
			max=arr[i];
	}
	return max;
}
int arr_pairs(int arr[],int n,int max)
{
	int i,j,c=0;
	for(i=0;i<n;i++)
		for(j=i+1;j<n;j++)
		{
			if(arr[i]*arr[j]<=max)
				c++;
		}
	return c;
}

