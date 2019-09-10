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
	int i,j,sum=1,k;
	long int area,max=0;
	arr[n]=0;
	for(i=0;i<n;i++)
	{
		for(j=1,k=i+1;j<=arr[i];j++)
		{
			while(j<=arr[k] && arr[k]!=0)
			{
				sum++;
				k++;
			}
			area=j*sum;
			if(max==0)
				max=area;
			if(area>max)
				max=area;
			k=i+1;
			sum=1;
		}
	}
	return max;


}

