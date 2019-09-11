#include<stdio.h>
#include<math.h>
int main()
{
	int i,c=0,n;
	scanf("%d",&n);
        for(i=1;i<=n;i++)
        {
                if(n%i==0)
                        c++;
        }
        if(c==2)
                printf("p\n");
        else
                printf("not prime\n");
}
