#include<stdio.h>
int main()
{
	char cal[12][12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
	char (*arr)[12];
	int i;
	arr=&cal;
	for(i=0;i<12;i++)
		printf("%c\t",arr[i][2]);
		
}


