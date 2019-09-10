# include <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

int main(){
	int fd,i,ret;
	unsigned char *filedata= NULL,*temp;

	fd = open("abc",O_RDWR);
	getchar();

	filedata = (char *) mmap((void*)0,6,PROT_READ|PROT_WRITE, MAP_SHARED,fd,0);	

	if(filedata == NULL){
		perror("Maping Failed");
		return -1;
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
	
	i = munmap(temp,6);
	getchar();
	if( i != 0)
		printf(" failed to unmap\n");
}
