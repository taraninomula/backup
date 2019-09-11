#include<stdio.h>
int main()
{
	int n=0x12345678;
	//printf("enter number in hexadecimal format\n");
	//scanf("%x",&n);
	char *p=(char *)&n;
	if(*p==(n&0x000000ff))
		printf("little endian\n");
	else
		printf("big endian\n");

}


