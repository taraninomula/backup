#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int func(char s1[],char s2[]);
int main(int main)
{
        int count;
	char *fn=(char *)malloc(sizeof(fn));
	printf("enter file name\n");
	scanf("%s",fn);
	char *str=(char *)malloc(sizeof(str));
	printf("enter string\n");
	scanf("%s",str);
	count=func(fn,str);
	printf("count = %d\n",count);
}
int func(char s1[],char s2[])
{
        char *temp=(char *)malloc(sizeof(temp));
        int i;
	int c=0;
        FILE *fp=fopen(s1,"r");
        if(fp==NULL)
                printf("error in opening file\n");
        while(!feof(fp))
        {
                fscanf(fp,"%s",temp);
		if(!strcmp(temp,s2))
			c++;
	}
        fclose(fp);
        if(fp==NULL)
                printf("error in closing file\n");
	return c;
}

