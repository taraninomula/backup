#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdio.h>
#include<string.h>
#include <fcntl.h>
#include <sys/mman.h>

void myMemCpy(void *dest, void *src, size_t n)
{
	int i=0;
   // Typecast src and dest addresses to (char *)
   char *csrc = (char *)src;
   char *cdest = (char *)dest;
 
   // Copy contents of src[] to dest[]
   //for (i=0; i<n; i++)
     //  cdest[i] = csrc[i];
   for (i=0; i<n; i++){
       *cdest = *csrc;
	cdest++;
	csrc++;
	}
}

int main(int argc,char *argv[])
{
	int i,ret,fd1,fd2;
	struct stat temp;
	char *buff1,*buff2;
	char *temp1=NULL,*temp2=NULL;
	
	fd1 = open(argv[1],O_RDONLY);
	if (fd1 < 0)
	perror("open1 Fails:");
	else
	printf("open1 Success\n");

	fd2 = open(argv[2],O_RDWR|O_CREAT,0666);
	if (fd2 < 0)
	perror("open2 Fails:");
	else
	printf("open2 Success\n");
	
	ret = fstat(fd1,&temp);
	if (ret < 0)
	perror("stat Fails:");
	else
	printf("stat sucess\n");

	printf("size of the abc file:%ld\n",temp.st_size);

	buff1 = (char *) mmap(0,temp.st_size,PROT_READ,MAP_PRIVATE,fd1,0);
	buff2 = (char *) mmap(0,temp.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd2,0);
	temp1=buff1;
	temp2=buff2;
	for(i=0;i<=temp.st_size;i++) {
		//printf("%c",*buff1);
		*buff2 = *buff1;
		buff1++;
		buff2++;
	}
        //memcpy(buff2,buff1,4);
        //myMemCpy(buff2,buff1,4);
//        printf("%s\n",buff2);	

	munmap(temp1,temp.st_size);
	munmap(temp2,temp.st_size);
	close(fd1);
	close(fd2);
	return 0;
}


