#include<stdio.h>
long largest_rectangle(int arr[],int n);
int main()
{
	int n,i;
	long int area;
	printf("enter number of buildings\n");
	scanf("%d",&n);
	int arr[n];
	printf("enter the heights of buildings\n");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	area=largest_rectangle(arr,n);
	printf("area is %ld\n",area);
}
long largest_rectangle(int arr[],int n)
{
	int i,j;
	long int area=0,min;
	//for(i=0;i<n;i++)
	//	printf("%d\t",arr[i]);
	for(i=0;i<n;i++)
	{
		for(j=0;arr[j]<=arr[i];j++)
		{
		}
		min=arr[i]*j-1;
		if(area==0)
			area=min;
		if(min>area)
			area=min;
	}
	return area;


}

