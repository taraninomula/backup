#include<stdio.h>
int main()
{
	FILE *fp1,*fp2;
	fp1=fopen("t1.txt","r");
	if(fp1==NULL)
		printf("error in opening file1\n");
	fp2=fopen("t2.txt","a+");
	if(fp2==NULL)
		printf("error in opening file2\n");
	char temp[100];
	int c=0;
	while(!feof(fp1))
	{
		fscanf(fp1,"%s",temp);
		c++;
		fprintf(fp2,"%s",temp);
		if(c==2 || c==4)
			fprintf(fp2,"%s","	");
		if(c==6)
		{
			fprintf(fp2,"%c",'\n');
			c=0;
		}
	}
	fclose(fp1);
	if(fp1==NULL)
		printf("error in closing file1\n");
	fclose(fp2);
	if(fp2==NULL)
		printf("error in closing file2\n");
}
