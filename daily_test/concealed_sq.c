#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,i,m=1,c=1,j,b=0,t,k=0;
	int n1=0;
	long int s;
	printf("enter number of digits\n");
	scanf("%d",&n);
	int arr[n];
	int *ptr=(int *)malloc(sizeof(int));
	printf("enter digits\n");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	while(m>0)
	{
		s=m*m;
		i=0;
		while(s)
		{
			c++;
			ptr=(int *)realloc(ptr,c*sizeof(int));
			ptr[i++]=s%10;
			s=s/10;
		}
		for(j=0;ptr[j]!=0;j++)
			b++;
		printf("\n");
		for(i=0,j=b-1;i<j;i++,j--)
		{
			t=ptr[i];
			ptr[i]=ptr[j];
			ptr[j]=t;
		}
		for(i=0;i<n;i++)
		{
			if(arr[i]==ptr[n1])
				k++;
			n1=n1+2;
		}
		if(k==n)
		{
			printf("max is %d\n",m);
			break;
		}
		b=0;
		k=0;
		n1=0;
		m++;
	}
}





