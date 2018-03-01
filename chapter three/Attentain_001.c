#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* This is a wrong allocate usage  */
/* memory allocated for b is smallier than 
 * the real size  */
/* But out put is normal without segament false  */
/* because one more char is used get out of the bound of b  */
/* and the char is not used by other process  */
int main( void )
{
    char a[10] = "hello";
    printf( "%lu\n", strlen( a ) );
    char *b = ( char * )malloc(
            sizeof( strlen( a ) ));
    strcpy( b, a );
    printf( "%s\n", b );
    return 0;
}
