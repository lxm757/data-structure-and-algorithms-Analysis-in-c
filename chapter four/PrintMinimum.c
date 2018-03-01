#include <stdio.h>
#include <limits.h>

int main( void )
{
    int a;
    /* Use minus sign to tell complier
     * that change number to negative number */
    a = -( int )( ( unsigned int ) ~0 >> 1);
    printf( "%d\n", a );
    /* Compiler do not change number to negative number
     * if minus sign unused  */
    /* The result should be -1 not minimum  */
    a = ( int )( ( unsigned int ) ~0 );
    printf( "%d\n", a );
    return 0;
}
