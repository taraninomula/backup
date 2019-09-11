#include<stdio.h>
#include<stdlib.h>
int main()
{
	int r,c,i,j;
	printf("enter rows and coloumns\n");
	scanf("%d%d",&r,&c);
	int **ptr=(int **)malloc(sizeof(int *)*r);
	printf("enter elements of array\n");
	for(i=0;i<r;i++)
	{
		 ptr[i]=(int *)malloc(sizeof(int)*c);
		for(j=0;j<c;j++)
		{
			
			scanf("%d",&ptr[i][j]);
		}
	}
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
			printf("%d\t",ptr[i][j]);
			printf("\n");
	}
			for(i=0;i<r;i++)
			{
				free(ptr[i]);
				ptr[i]=NULL;
			}
			free(ptr);
			ptr=NULL;
		
}


