#include <stdio.h>

void my_fun1(int x)
{
	printf ("my_func1:x value:%d\n",x);
}
void my_fun2(int x)
{
	printf ("my_func2:x value:%d\n",x);
}

void (*fptr) (int); // function pointer declaration

int main ()
{

fptr = &my_fun1; //Function pointer Initalization

(*fptr)(4); // function pointer invoke

fptr = &my_fun2; //Function pointer Initalization
(*fptr)(4); // function pointer invoke


return 0;
}

