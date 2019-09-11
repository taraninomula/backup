#include <stdio.h>
 
int main()
{
	   int i,f,l,m,n,s,arr[100];
	   printf("Enter number of elements\n");
	   scanf("%d",&n);
	   printf("Enter integers\n");
	   for (i=0;i<n;i++)
		   scanf("%d",&arr[i]);
	   printf("Enter value to search\n");
	   scanf("%d", &s);
	   f=0;
	   l=n-1;
	   m=(f+l)/2;
	   while(f<=l)
	   {
		   if(arr[m]<s)
			   f=m+1;
		   else if(arr[m]==s)
		   {
			   printf("%d found at location %d\n",s,m);
			   break;
		   }
			   else
				   l=m-1;
			   m=(f+l)/2;
			   if(f>l)
				   printf("Not found\n");
	   }
					       
}

