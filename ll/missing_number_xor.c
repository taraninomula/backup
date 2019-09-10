#include<stdio.h>
int main()
{
	int n,m,s=0,l=0,i;
	printf("enter number of elements\n");
	scanf("%d",&n);
	int arr[n];
	printf("enter number of elements\n");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	for(i=0;i<n;i++)
		s=s^arr[i];
	for(i=1;i<=n+1;i++)
		l=l^i;
	m=l^s;
	printf("missing number is %d\n",m);
}
		

