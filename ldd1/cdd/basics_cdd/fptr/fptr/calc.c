#include <stdio.h>

int add(int x,int y)
{
	printf ("add\n");
	return x+y;
}
int sub(int x, int y)
{
	printf ("sub\n");
	return x-y;
}

int (*fptr) (int, int); // function pointer declaration

int main ()
{

char temp;
printf("User enter A: add S: sub\n");
scanf("%c",&temp);

switch (temp)
{
	case 'A':
		fptr=&add;
		printf("add result:%d\n",(*fptr)(5,4));
		break;
	case 'S':
		fptr=&sub;
		printf("Sub result:%d\n",(*fptr)(5,4));
		break;
	default:
		printf("option is wrong\n");
}

return 0;
}

