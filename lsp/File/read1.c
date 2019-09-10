#include<unistd.h>
#include<stdio.h>
#include<errno.h>

int main()
{
int ret;
char buff[100];
	ret = read(3,&buff,6);
	if (ret < 0)
	{
	perror("Read Fails");
	printf("errno:%d\n",errno);
	return -1;
	}
	printf("ret:%d buff:%s\n",ret,buff);

}

