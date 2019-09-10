#include<stdio.h>
int main()
{
    int t;
    long long int i=1,m=2;
    scanf("%d",&t);
    for(int a0 = 0; a0 < t; a0++){
        int n,c=0;
        scanf("%d",&n);
        while(m>0)
        {
         for(i=1;i<=n;i++)
         {
             if(m%i==0)
                 c++;
         }
            if(c==n)
                break;
            c=0;m++;
        }
        printf("%lld\n",m);
    }
    return 0;
}

