#include <stdio.h>
#include <string.h>
int count(char * str, char * toSearch);
int main()
{
	    char str[200];
	    char sub[100];
	    int c;
	    printf("Enter any string: ");
            scanf("%[^\n]s",str);
	    printf("Enter word to search occurrences: ");
	    scanf("%s",sub);
	    c = count(str,sub);
	    printf("count is %d\n",c);

			
}

int count(char * str, char * sub)
{
	int i,j,f,c;
	int l1,l2;
	l1=strlen(str);
	l2=strlen(sub);
	c = 0;
	for(i=0;i<=l1-l2;i++)
	{
		f=1;
		for(j=0;j<l2;j++)
		{
			if(str[i+j]!=sub[j])
			{
				f=0;
				break;
			}
		}                                                  
		if(f==1)
		{
			c++;
		}
									        
	}
	return c;
}
