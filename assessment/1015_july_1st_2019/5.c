#include<stdio.h>
int main()
{
	int n,sum=0,a,m;
	printf("enter a number\n");
	scanf("%d",&n);
	m=n;
	while(n!=0)
	{
		a=n%10;
		sum=sum*10+a;
		n=n/10;
	}
	if(m==sum)
		printf("palindrome\n");
	else
		printf("not palindrome\n");
}
