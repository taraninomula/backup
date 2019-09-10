# include <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>


int main(int arg_count, char *arg_var[] ){

	int fd,i,ret;
	int length,offset;
	unsigned char *filedata= NULL,*temp;
	struct stat temp1;

	if ((arg_count > 4 ) | (arg_count < 3) )
	{
	printf ("usage: ./a.out <filename> <length> [offset]");
	return -1;
	}

	fd = open(arg_var[1],O_RDWR);
	getchar();
	ret = fstat(fd, &temp1);
	printf ("File size:%lx\n",temp1.st_size);
	if (temp1.st_size == 0)
	{
	printf ("File size is EMPTY\n");
	return -1;
	}

	length = atoi(arg_var[2]);
	offset = atoi(arg_var[3]);
	if (offset > temp1.st_size )
	{
		printf ("offset is greater than file size\n");
		return -1;
	}

	printf ("length:%d offset:%d\n",length,offset);

	filedata = (char *) mmap((void*)0,length,PROT_READ|PROT_WRITE, MAP_PRIVATE,fd,offset);	

	if(filedata == NULL){
		perror("Maping Failed");
		return -1;
	}

	getchar();
	// now we can access the content of the file as if it is part of
	// our process starting from the memory pointed by filedata.
	temp = filedata;
	for(i=0;i<10;i++,filedata++)
	{
		*filedata = (char)(i+65);
		printf("\n %c\n",(char)(i+65));
	}
//	if(msync(temp,100,MS_SYNC)!=0)
//		perror("msync : ");
	
	i = munmap(temp,10);
	getchar();
	if( i != 0)
		printf(" failed to unmap\n");
        return 0;
}
