#include<stdio.h>
main()
{
	int a=10,b=5;
#if NUM==1
	printf("%d\n",a+b);
#endif
#if NUM==2
	printf("%d\n",a-b);
#endif
}
