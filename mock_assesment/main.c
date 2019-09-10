#include<stdio.h>
#include<string.h>
void read_word(char input[],char output[]);
void write_word(char temp[]);
void remove_duplicates(char temp[]);
int casecmp(char temp[],char str[]);
FILE *fpi=NULL;
FILE *fpo=NULL;
char arr[100];
int main()
{
	char input_file[100],output_file[100];
	printf("enter input file name\n");
	scanf("%s",input_file);
	printf("enter output file name\n");
	scanf("%s",output_file);
	read_word(input_file,output_file);
}
void read_word(char input[],char output[])
{
	char temp[100],temp1[100];
	fpi=fopen(input,"r");
        if(fpi==NULL)
                printf("failed to open input file\n");
	fpo=fopen(output,"r+");
        if(fpo==NULL)
                printf("failed to open input file\n");
	while(!feof(fpi))
	{
		fscanf(fpi,"%s",temp);
		remove_duplicates(temp);
		//memset(temp,'\0',sizeof(temp));
	}
}
void remove_duplicates(char temp[])
{
	fscanf(fpi,"%s",temp);
        fprintf(fpo,"%s",temp);
        fprintf(fpo,"%s"," ");
	//memset(arr,'\0',sizeof(arr));
	fseek(fpo,0,SEEK_SET);

	while(!feof(fpo))
	{
		fscanf(fpo,"%s",arr);
		printf("output %s\n",arr);
		//printf("func %s\n",temp);
		if(strcasecmp(temp,arr)==0)
		{
		}
		else if(strcasecmp(temp,arr)!=0)
		{
			fprintf(fpo,"%s",temp);
			fprintf(fpo,"%s"," ");
			//memset(arr,'\0',sizeof(arr));
		}
	}
}		
int casecmp(char temp[],char str[])
{
	int i,a;
	for(i=0;temp[i]!='\0' && str[i]!='\0';i++)
        {
                if((temp[i]-str[i]==32) || (str[i]-temp[i])==32 || (temp[i]==str[i]))
			a=0;
                else if(temp[i]!=str[i])
                {
                        a=1;
                        break;
                }
        }

	return a;
}


