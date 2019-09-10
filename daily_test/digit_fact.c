#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int fact(int n)
{
    int i,r=1;
    if(n!=0)
    {
	    for(i=1;i<=n;i++)
		    r=r*i;
	    return r;
    }
    else
	    return 0;

}

int main() 
{
    long int n,mul=1,sum=0;
    int a,b,i;
    scanf("%ld",&n);
    for(i=10;i<=n;i++)
    {
	    b=i;
        while(b)
        {
	    a=b%10;
	    b=b/10;
	    if(fact(a)!=0)
            mul=mul*fact(a);
        }
        if(mul%i==0)
            sum=sum+mul;
	mul=1;
    }
    printf("%ld\n",sum);


    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
