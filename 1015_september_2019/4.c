#include<stdio.h>
int main()
{
	int n;
	int sum=0;
	printf("enter number of elements\n");
	scanf("%d",&n);
	printf("enter elements\n");
	int i,arr[n];
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(i=0;i<n;i++)
		sum=sum+arr[i];
	printf("%d\n",sum);
	float avg;
	avg=((float)sum/n);
	printf("average is %.3f\n",avg);
}
