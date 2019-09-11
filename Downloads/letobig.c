/*littile endian to big endien convertion using union*/

/*#include<stdio.h>
union con
{
int n;
char c[4];
}s;
main()
{
char t;
printf("enter num\n");
scanf("%x",&s.n);
t=s.c[0];
s.c[0]=s.c[3];
s.c[3]=t;
t=s.c[1];
s.c[1]=s.c[2];
s.c[2]=t;
printf("%x\n",s.n);
}*/

#include<stdio.h>
#include<stdlib.h>
main()
{
char t;
int n;
printf("enter num\n");
scanf("%i",&n);
char *p = &n;
//char *t=&n;
t=*(p+3);
*(p+3)=*(p+0);
*(p+0)=t;
t=*(p+1);
*(p+1)=*(p+2);
*(p+2)=t;
printf("%x\n",n);
}

