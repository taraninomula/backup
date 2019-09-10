# include  <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>


main(int arg_count, char *arg_var[] ){

	int fd,i,ret,len,pos;
	unsigned char *filedata= NULL,*temp;
	struct stat temp1;

	if ((arg_count > 4 ) | (arg_count < 3) )
	{
	printf ("usage: ./a.out <filename> <length> [offset]\n");
	exit(0);
	}
	printf ("arg_count:%d arg_var[0]:%s arg_var[1]:%s arg_var[2]:%s arg_var[3]:%s\n",arg_count,arg_var[0],arg_var[1],arg_var[2],arg_var[3]);
	fd = open(arg_var[1],O_RDWR);
	getchar();
	ret = fstat(fd, &temp1);
	printf ("File size:%d\n",temp1.st_size);
	if (temp1.st_size == 0)
	{
	printf ("File size is EMPTY\n");
	exit (0);
	}
	
	len = atoi(arg_var[2]);
        printf ("len:%d\n",len);

	if (arg_count == 3)
	pos=0;
	else
	pos = atoi(arg_var[3]);

        printf ("pos:%d\n",pos);
	filedata = (char *) mmap((void*)0,len,PROT_READ|PROT_WRITE, MAP_SHARED,fd,pos);	

	if(filedata == NULL){
		perror("Maping Failed");
		exit(1);
	}

	getchar();
	// now we can access the content of the file as if it is part of
	// our process starting from the memory pointed by filedata.
	temp = filedata;
	for(i=0;i<4;i++,filedata++)
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
}
