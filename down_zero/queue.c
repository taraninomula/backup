#include<stdio.h>
#include<stdlib.h>
int down_zero(int n);
int mid_factor(int n);
int max(int a,int b);
typedef struct down{
    int num;
    int level;
}d;

int main()
{
	int n,c;
	printf("enter number\n");
	scanf("%d",&n);
	c=down_zero(n);
	printf("%d\n",c);
}
int down_zero(int n)
{
	d *arr=(d*)malloc(sizeof(d));
    int i,j=1,k;
    arr[0].num = n;
    arr[0].level = 0;
    if(n<=3)
        return n;
    for(i=0;arr[i].num;i++)
    {
        arr=(d*)realloc(arr,(j+1)*sizeof(d));
        arr[j].num = ((arr[i].num) -1);
        arr[j].level = (arr[i].level)+1;
        if(arr[j].num == 2)
            return (arr[j].level + 2);
        j++;
      
                arr=(d *)realloc(arr,(j+1)*sizeof(d));
		if(mid_factor(arr[i].num)!=1)
		{
                arr[j].num = max(arr[i].num/mid_factor(arr[i].num),mid_factor(arr[i].num));
                arr[j].level = (arr[i].level)+1;
		}
		else
		{
			arr[j].num = ((arr[i].num) -1);
		arr[j].level = (arr[i].level)+1;
		}
                if(arr[j].num ==2 )
                    return (arr[j].level)+2;
                j++;
           
    }
    return arr[j].level;
     free(arr);
}
int max(int a,int b)
{
        if(a>b)
                return a;
        else
                return b;
}

int mid_factor(int n)
{
	int m,i,j=0,a[100];
	for(i=1;i<=n; i++)
	{
		if (n%i == 0)
		{
			a[j]=i;
			j++;
		}
	}
	if(j%2==0)
		m=a[(j/2)-1];
	else
		m=a[(j/2)];
	return m;
}
