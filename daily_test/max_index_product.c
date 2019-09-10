#include<stdio.h>
int left(int arr[],int n,int index);
int right(int arr[],int n,int index);
int main()
{
	int n,i,l,r,max=0,t;
	printf("enter no of elements\n");
	scanf("%d",&n);
	int arr[n];
	printf("enter elements\n");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(i=0;i<n;i++)
	{
		l=left(arr,n,i);
		r=right(arr,n,i);
		t=l*r;
		if(max==0)
			max=t;
		if(max<t)
			max=t;
	}
	printf("max product is %d\n",max);
}
int left(int arr[],int n,int index)
{
	int l=0,i;
	for(i=index-1;i>=0;i--)
	{
		if(arr[i]>arr[index])
		{
			l=i+1;
			break;
		}
	}
	return l;
}
int right(int arr[],int n,int index)
{
	int r=0,i;
	for(i=index+1;i<n;i++)
	{
		if(arr[i]>arr[index])
		{
			r=i+1;
			break;
		}
	}
	return r;
}


