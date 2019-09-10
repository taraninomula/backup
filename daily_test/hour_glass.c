#include<stdio.h>
int main()
{
	int arr[6][6],i,j;
	int s1,s2,s3,s,max=0;
	printf("enter elements of array\n");
	for(i=0;i<6;i++)
		for(j=0;j<6;j++)
			scanf("%d",&arr[i][j]);
	for(i=0;i<6;i++)
	{
                for(j=0;j<6;j++)
		{
			printf("%d\t",arr[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			s=arr[i][j]+arr[i][j+1]+arr[i][j+2]+arr[i+1][j+1]+arr[i+2][j]+arr[i+2][j+1]+arr[i+2][j+2];
			printf("%d ",arr[i][j]);
			printf("s %d\n",s);
			if(max==0)
            max=s;
            if(s>max)
            max=s;
			
		
		}
	}
	printf("%d\n",max);
}

