#include<stdio.h>
#include<stdlib.h>
void rotation(int *ptr,int size);
int main(int argc,char *argv[1])
{
	int i,j,temp,size,rot;
	if(argc==3)
	{
		size=atoi(argv[1]);
		rot=atoi(argv[2]);
		int *ptr=(int *)malloc(size*sizeof(int));
		printf("Enter the elements\n");
		for(i=0;i<size;i++)
			scanf("%d",&ptr[i]);
		for(i=0;i<size;i++)
			printf("%d ",ptr[i]);
		for(j=0;j<rot;j++)
		{
			rotation(ptr,size);
		}
		printf("array after rotating\n");
		for(i=0;i<size;i++)
		{
			printf("%d ",ptr[i]);
		}
	}
	else
		printf("wrong command line arguments\n");
}
void rotation(int *ptr,int size)
{
	int temp,i;
	temp=ptr[0];
	for(i=0;i<size-1;i++)
	{
		ptr[i]=ptr[i+1];
	}
	ptr[size-1]=temp;
}

