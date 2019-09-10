//i/p : {abc,bc,ca,bc} and {abc ca bc}  o/p :{1,1,2}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
# define max 10
int* fun(char **ptr,char **q,int *r,int n,int m);
int main()
{
	int n,m,i;
	printf("enter how many input strings do u want to create\n");
	scanf("%d",&n);
	char **ptr=(char **)malloc(sizeof(char *)*n);
        for(i=0;i<n;i++)
                ptr[i]=(char *)malloc(max*sizeof(char));
        for(i=0;i<n;i++)
                scanf("%s",ptr[i]);
        for(i=0;i<n;i++)
                printf("%s\t",ptr[i]);
        printf("\n");
        printf("enter how many input strings do u want to create\n");
        scanf("%d",&m);
        char **q=(char **)malloc(sizeof(char *)*m);
        for(i=0;i<m;i++)
                q[i]=(char *)malloc(max*sizeof(char));
        for(i=0;i<m;i++)
                scanf("%s",q[i]);
        for(i=0;i<m;i++)
                printf("%s\t",q[i]);
        int *r=(int *)malloc(m*sizeof(int));

	r=fun(ptr,q,r,n,m);
	for(i=0;i<m;i++)
                printf("%d\t",r[i]);
        printf("\n");

}
int* fun(char **ptr,char **q,int *r,int n,int m)
{
	int i,j;
	for(i=0;i<m;i++)
		r[i]=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if(strcmp(ptr[i],q[j])==0)
				++r[j];
		}
	}
	return r;
}

