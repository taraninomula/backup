#include<stdio.h>
void print(int arr[],int n);
void quicksort(int arr[],int l,int h);
int div(int arr[],int l,int h);
void swap(int *a,int *b);
int main()
{
	int n,i;
	printf("enter number of elements in array\n");
	scanf("%d",&n);
	int arr[n];
	printf("enter elements in array\n");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	quicksort(arr,0,n-1);
	printf("after sorting\n");
	print(arr,n);
}
void print(int arr[],int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d\t",arr[i]);
	printf("\n");
}
void quicksort(int arr[],int l,int h)
{
	if(l<h)
	{
		int p=div(arr,l,h);
		quicksort(arr,l,p-1);
		quicksort(arr,p+1,h);
	}
}
int div(int arr[],int l,int h)
{
	int piv=arr[h];
	int i=l-1;
	int j;
	for(j=l;j<=h-1;j++)
	{
		if(arr[j]<=piv)
		{
			i++;
			swap(&arr[i],&arr[j]);
		}
	}
	swap(&arr[i+1],&arr[h]);
	return (i+1);
}
void swap(int *a,int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}


