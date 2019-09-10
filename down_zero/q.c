#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int down_zero(int n);
int main()
{
	int n,c;
        printf("enter number\n");
        scanf("%d",&n);
        c=down_zero(n);
        printf("%d\n",c);
}
int down_zero(int n)
{
	int i,j=1,level=0,k,a;
	int *ptr1=(int*)malloc(sizeof(int));
	int *ptr2=(int*)malloc(sizeof(int));
	ptr1[0]=n;
	a=1;
	while(1)
	{
		k=0;
		if(ptr1[k]==0)
                        return level;
		for(k=0;k<a;k++)
		{
			for(i=1;i<=sqrt(ptr1[k]); i++)
			{
				if (ptr1[k]%i==0)
				{
					if(i!=1)
					{
						ptr2=(int*)realloc(ptr2,j*sizeof(int));
						ptr2[j-1]=ptr1[k]/i;
						j++;
					}
					else
					{
						ptr2=(int*)realloc(ptr2,j* sizeof(int));
						ptr2[j-1]=ptr1[k]-1;
						j++;
					}
				}
			}
		}
//		if(k>=a)
//		{
			a=j-1;
			ptr1=(int*)realloc(ptr1,(j-1)*sizeof(int));
			memcpy(ptr1,ptr2,(j-1)*sizeof(int));
			j=1;
			level++;
		//}
		//if(ptr1[k]==0)
		//	return level;
	}
}

