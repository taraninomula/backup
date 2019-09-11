#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int str_len(char buf[]);
//#define ARRAY_SIZE 10
int main(int argc,char *argv[])
{
	unsigned char *buf;
	int i,len;
	//buf=malloc(sizeof(int));
	buf=(unsigned char*)malloc(len*sizeof(unsigned char));
	printf("Take i/p from user\n");
	scanf("%s",buf);
	printf("buf is %s\n",buf);
	len=str_len(buf);
	printf("strlen of buf is : %d\n",len);
		for(i=0;buf[i]!='\0';i++)
		{
		
			buf[i]=buf[i]+1;

		
		}

	printf("modified string is:%s\n",buf);
	return 0;

}
int str_len(char buf[])
{
	int count=0,i=0;
	while(buf[i]!='\0')
	{
		count++;
		i++;
	} 
	return count;
}


