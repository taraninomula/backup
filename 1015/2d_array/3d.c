#include<stdio.h>
#include<stdlib.h>
int main()
{
	int r,c,i,j,n,k,m=1;
	printf("enter no of matrices and rows and coloumns\n");
	scanf("%d%d%d",&n,&r,&c);
	int ***ptr=(int ***)malloc(sizeof(int **)*n);
	for(k=0;k<n;k++)
	{
		ptr[k]=(int **)malloc(sizeof(int *)*r);
		printf("enter elements of matrix%d\n",m++);
		for(i=0;i<r;i++)
		{
			ptr[k][i]=(int *)malloc(sizeof(int)*c);
			for(j=0;j<c;j++)
			{
				scanf("%d",&ptr[k][i][j]);
			}
		}
	}
	for(k=0;k<n;k++)
	{
		for(i=0;i<r;i++)
		{
			for(j=0;j<c;j++)
				printf("%d\t",ptr[k][i][j]);
			printf("\n");
		}
		printf("\n");

	}
	for(k=0;k<n;k++)
	{
		for(i=0;i<r;i++)
		{
			free(ptr[k][i]);
			ptr[k][i]==NULL;
		}
		free(ptr[k]);
		ptr[k]=NULL;
	}
	free(ptr);
	ptr=NULL;
		
}


