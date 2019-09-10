#include<stdio.h>
int main()
{
	int n;
	printf("enter size of array\n");
	scanf("%d",&n);
	int arr[n],i,j,or[n],k=0;
	printf("enter elements of array in sorted way\n");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(arr[i]!=arr[j])
			{
				arr[k]=arr[i];
				k++;
			}
		}
	}



