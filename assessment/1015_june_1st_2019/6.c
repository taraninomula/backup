
#include<stdio.h>
int main()
{
        int c=0,i,j,k,l=0,s,p=0,n=432;
        printf("enter number of elements in array\n");
        scanf("%d",&s);
        int arr[s];
        printf("enter elements of array\n");
        for(i=0;i<s;i++)
                scanf("%d",&arr[i]);
	for(i=-1;i<s-1;i++)
	{
		for(j=i+1,k=j+1;j!=n;j++,k++)
		{
			if(j==s-1)
			{
				p=1;
				k=i+1;
			}
			if(arr[j]>arr[k])
				c++;
			else
				c=0;
			if(p==1)
			{
				j=-1;
				p=0;
			}
			n=i+1;
			
		}
		if(c>l)
			l=c;
	}
	printf("count is %d\n",++l);
}
	

       



