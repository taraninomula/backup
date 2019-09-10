#include<stdio.h>
#include<string.h>
#include<unistd.h>
char temp[100],arr[100];
void read_word(void);
FILE *fpi=NULL;
FILE *fpo=NULL;
int main()
{
	char input_file[100],output_file[100];
        printf("enter input file name\n");
        scanf("%s",input_file);
        printf("enter output file name\n");
        scanf("%s",output_file);
	fpi=fopen(input_file,"r");
        if(fpi==NULL)
                printf("failed to open input file\n");
        fpo=fopen(output_file,"r+");
        if(fpo==NULL)
                printf("failed to open input file\n");
	read_word();
	fclose(fpi);
	fclose(fpo);

}

void read_word(void)
{
	fscanf(fpi,"%s",temp);
	fprintf(fpo,"%s",temp);
	fprintf(fpo,"%s"," ");
	while (!feof(fpi))
	{
		fscanf(fpi,"%s",temp);
		//printf("%s\t",temp);
		fseek(fpo,0,SEEK_SET);
		while(!feof(fpo))
		{
			fscanf(fpo,"%s",arr);
			//printf("%s\t",arr);
			if(strcasecmp(temp,arr)==0)
				break;
			memset(arr,'\0',sizeof(arr));
		}
		if(strcasecmp(temp,arr)!=0)
		{
			fprintf(fpo,"%s",temp);
			fprintf(fpo,"%s"," ");
			memset(temp,'\0',sizeof(temp));
		}
	}
}
int casecmp(char temp[],char str[])
{
        int i,a;
        for(i=0;temp[i]!='\0' &&  str[i]!='\0';i++)
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

