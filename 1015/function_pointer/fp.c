#include<stdio.h>
#include<stdlib.h>
void add(int a,int b);
void sub(int a,int b);
void mul(int a,int b);
void divi(int a,int b);
void fp1(void (*print1)(int a,int b),int id);
void fp2(void (*print2)(int a,int b),int id);
int main()
{
	typedef void (*arr_fp)(void (*print)(int a,int b),int id);
	arr_fp *more_fp;
	more_fp=(arr_fp *)malloc(sizeof(arr_fp *)*2);
	more_fp[0]=(arr_fp)&fp1;
	more_fp[1]=(arr_fp)&fp2;
	more_fp[0](add,0);
	more_fp[0](sub,0);
	more_fp[1](mul,1);
	more_fp[1](divi,1);
}
void fp1(void (*print1)(int a,int b),int id)
{
	print1(4,3);
	printf("index is %d\n",id);
}
void fp2(void (*print2)(int a,int b),int id)
{
	print2(8,2);
	printf("index is %d\n",id);
}
void add(int a,int b)
{
	printf("add=%d\n",a+b);
}
void sub(int a,int b)
{
	printf("sub=%d\n",a-b);
}
void mul(int a,int b)
{
	printf("mul=%d\n",a*b);
}
void divi(int a,int b)
{
	printf("div=%d\n",a/b);
}





