// function pointer is a variable that stores the address of a fucntion

#include <stdio.h>
void my_int_func(int x)
{
    printf( "%d\n", x );
}


int main()
{
    void (*hello)(int); // function pointer Declaration
    hello = &my_int_func; // function pointer initialization

    /* call my_int_func (note that you do not need to write (*hello)(2) ) */
    hello( 2 );
    /* but if you want to, you may */
    (*hello)( 2 );

    return 0;
}

