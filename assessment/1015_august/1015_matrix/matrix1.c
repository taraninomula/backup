#include<stdio.h>
#include<stdlib.h>
int sum=0,ca,ra,m=1;
void fun(int **ptr,int i,int j);
int main()
{
	int r,c,i,j,k,l,dsum1=0,dsum2=0,dsum;
	int **ptr;
	printf("enter rows and coloumns\n");
	scanf("%d%d",&r,&c);
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
	if(r%3!=0 || c%3!=0)
	{
		ra=r+(3-r%3);
		ca=r+(3-c%3);
		ptr=(int **)realloc(ptr,sizeof(int *)*ra);
		printf("enter elements of array\n");
		for(i=0;i<ra;i++)
		{
			ptr[i]=(int *)realloc(ptr[i],sizeof(int)*ca);
		}
		for(i=0;i<ra;i++)
		{
			for(j=0;j<ca;j++)
			{
				if(i>=r || j>=c)
				ptr[i][j]=1;
			}
		}
	

	}
	else
	{
		ra=r;
		ca=c;
	}
	for(i=0;i<ra;i++)
	{
		for(j=0;j<ca;j++)
		{
			printf("%d\t",ptr[i][j]);
			if(i==j)
				dsum1=dsum1+ptr[i][j];
			if(i+j==ra-1)
				dsum2=dsum2+ptr[i][j];
		}
		printf("\n");
	}
	for(i=0;i<ra;i=i+3)
	{
		for(j=0;j<ca;j=j+3)
		{
			fun(ptr,i,j);
		}
	}
	dsum=dsum1+dsum2;
	printf("sum of diagnol1= %d,sum of diagnol2=%d\n",dsum1,dsum2);
	printf("sum of diagnols =%d\n",dsum);
	for(i=0;i<3;i++)
	{
		free(ptr[i]);
		ptr[i]=NULL;
	}
	free(ptr);
	ptr=NULL;
}
void fun(int **ptr,int i,int j)
{
	int k,l;
	for(k=i;k<i+3 && k< ra;k++)
	{
		for(l=j;l<j+3 && l<ca ;l++)
			sum=sum+ptr[k][l];
	}
	printf("sum of block%d=%d\n",m++,sum);
	sum=0;
}

