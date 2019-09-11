#include<stdio.h>
#include<string.h>
char* func1(char s1[],char s2[]);
char* func2(char s3[],char s4[]);
int main(int argc,char *argv[])
{
	//printf("%s\n",argv[1]);
	//printf("%s\n",argv[2]);
	func1(argv[1],argv[2]);
}
char * func1(char s1[],char s2[])
{
	char temp[100];
	int i;
	FILE *fp=fopen(s1,"a+");
	printf("%s\n",s1);
	if(fp==NULL)
		printf("error in opening file\n");
	while(!feof(fp))
	{
		fscanf(fp,"%s",temp);
		temp[100]=func2(temp,s2);
	}
	fclose(fp);
	if(fp==NULL)
		printf("error in closing file\n");
}
char *func2(char s3[],char s4[])
{
	char rev;
	int i,j,l;
	if(!strcmp(s3,s4))
	{
		l=strlen(s3)-1;
		printf("%d\n",l);
		printf("word found\n");
		printf("%s\n",s3);
		for(i=0;i<strlen(s3)/2;i++)
		{
			rev=s3[i];
			s3[i]=s3[l];
			s3[l--]=rev;
		}
		//printf("%s\n",s3);
		return s3;
	}

}
			


		
