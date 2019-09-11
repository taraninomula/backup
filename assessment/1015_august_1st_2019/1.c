#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[])
{
	char temp[100],ch;
	char s1[3]="-l";
	char s2[3]="-i";
	char s3[3]="-n";
	int i,c=0,l=1;
	FILE *fp=fopen(argv[1],"r");
	if(fp==NULL)
		printf("error in opening file\n");
	while(!feof(fp))
	{
		fscanf(fp,"%s",temp);
		ch=fgetc(fp);
		if(ch=='\n')
			l++;
		if(argc==3)
		{
			if(strcmp(argv[2],temp)==0)
			{
				printf("word found\n");
				c=1;
			}
		}
		else if(argc==4)
		{
			if(strcmp(argv[3],s2)==0)
			{
				if(strcasecmp(argv[2],temp)==0)
				{
					c=1;
					printf("word found\n");
				}
			}
			else if(strcmp(argv[3],s1)==0)
			{
				if(strccmp(argv[2],temp)==0)
				{
					c=1;
					printf("word found in line no %d\n",l);
				}
			}

		}

	}
	if(argc==4)
	{
		if(strcmp(argv[3],s3)==0)
				printf("file name is %s\n",argv[1]);

	}
	if(c==0)
		printf("word not found\n");
	fclose(fp);
	if(fp==NULL)
		printf("error in closing file\n");
}

			



		
