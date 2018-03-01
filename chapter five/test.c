#include <stdio.h>

int main( void )
{
    int a;
    while( 1 )
    {
        scanf( "%d", &a );
        printf( "%d\n", 7 - ( a % 7 ) );
    }
    return 0;
}
