#include<stdio.h>
void fun(int arr_count,int * arr);
int main()
{
	int arr[5],i,j,k;
	printf("enter 5 integer elements\n");
	for(i=0;i<5;i++)
		scanf("%d",&arr[i]);
	fun(5,arr);
}
void fun(int arr_count,int * arr)
{
	int i,j,k;
	long int minsum=0,maxsum=0;
	for(i=0;i<arr_count;i++)
	{
		for(j=i+1;j<arr_count;j++)
		{
			if(arr[i]>arr[j])
			{
				k=arr[i];
				arr[i]=arr[j];
				arr[j]=k;
			}
		}
	}
	printf("after sorting\n");
	for(i=0;i<arr_count;i++)
		printf("%d\n",arr[i]);
	for(i=0;i<arr_count-1;i++)
		minsum=minsum+arr[i];
	for(i=1;i<arr_count;i++)
		maxsum=maxsum+arr[i];
	printf("%ld %ld\n",minsum,maxsum);

}


