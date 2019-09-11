#include<stdio.h>
#include<stdlib.h>
int main()
{
	int r,c,i,j,sum=0,dsum1=0,dsum2=0;
	int **ptr;
	printf("enter rows and coloumns\n");
	scanf("%d%d",&r,&c);
	if(r%3==0 && c%3==0)
	{
		ptr=(int **)malloc(sizeof(int *)*r);
		printf("enter elements of array\n");
		for(i=0;i<r;i++)
		{
			ptr[i]=(int *)malloc(sizeof(int)*c);
			for(j=0;j<c;j++)
			{
				scanf("%d",&ptr[i][j]);
			}
		}
	}
	else
	{
		ptr=(int **)malloc(sizeof(int *)*3);
		printf("enter elements of array\n");
		for(i=0;i<3;i++)
		{
			ptr[i]=(int *)malloc(sizeof(int)*3);
			for(j=0;j<3;j++)
			{
				if(i!=2 && j!=2)
					scanf("%d",&ptr[i][j]);
				if(i==2 || j==2)
					ptr[i][j]=1;
			}
		}
	}
	if(r%3==0 && c%3==0)
	{

	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("%d\t",ptr[i][j]);
			sum=sum+ptr[i][j];
			if(i==j)
				dsum1=dsum1+ptr[i][j];
			if(i+j==r|i+j==0)
				dsum2=dsum2+ptr[i][j];

		}
		printf("\n");
	}
	printf("sum =%d\n",sum);
	printf("sum of diagnol 1 = %d\n",dsum1);
	printf("sum of diagnol 2= %d\n",dsum2);
	}
	else
	{
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				printf("%d\t",ptr[i][j]);
				sum=sum+ptr[i][j];
				if(i==j)
					dsum1=dsum1+ptr[i][j];
				if(i+j==2)
					dsum2=dsum2+ptr[i][j];
			}
			printf("\n");
		}
		printf("sum =%d\n",sum);
		printf("sum of diagnol 1 = %d\n",dsum1);
		printf("sum of diagnol 2 = %d\n",dsum2);
	}

	for(i=0;i<3;i++)
	{
		free(ptr[i]);
		ptr[i]=NULL;
	}
	free(ptr);
	ptr=NULL;
}
