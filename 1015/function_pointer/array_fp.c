#include<stdio.h>
#include<stdlib.h>
void print1_good();
void print2_good();
void print3_good();
void print1_bad();
void print2_bad();
void print3_bad();
void fp1(void (*print_good)());
void fp2(void (*print_bad)());
int main()
{
	typedef void (*arr_fp)(void (*print)());
	arr_fp *more_fp;
	more_fp=(arr_fp *)malloc(sizeof(arr_fp *)*2);
	more_fp[0]=(arr_fp)&fp1;
	more_fp[1]=(arr_fp)&fp2;
	more_fp[0](print1_good);
	more_fp[0](print2_good);
	more_fp[0](print3_good);
	more_fp[1](print1_bad);
	more_fp[1](print2_bad);
	more_fp[1](print3_bad);
}
void fp1(void (*print_good)())
{
	print_good();
}
void fp2(void (*print_bad)())
{
	print_bad();
}
void print1_good()
{
	printf("good morning\n");
}
void print2_good()
{
	printf("good evening\n");
}
void print3_good()
{
	printf("good night\n");
}
void print1_bad()
{
	printf("bad morning\n");
}
void print2_bad()
{
	printf("bad evening\n");
}
void print3_bad()
{
	printf("bad night\n");
}





