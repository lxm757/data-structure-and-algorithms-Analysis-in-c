#include "LinkedListP.h"
#include <stdlib.h>
#include <stdio.h>

/* Test  */
int main( void )
{
    Position FindX( ElementType, List );
    List L = NULL;
    L = Create( );

    Insert( 11, Last( L ), L );
    Insert( 13, Last( L ), L );
    Insert( 15, Last( L ), L );
    Insert( 17, Last( L ), L );

    Print( L );
    putchar( '\n' );

    Position P;
    P = FindX( 15, L );
    printf( "Find %d\n", P->Element );

    DeleteList( L );

    return 0;
}

/* Return position of X  */
/* Recursively implementation */
/* This is a bad function  */
/* Waste lots of space  */
Position FindX( ElementType X, List L )
{
    if( L->Next == NULL )
    {
        return NULL;
    }
    if( L->Next->Element == X )
    {
        return L->Next;
    }
    return FindX( X, L->Next );
}
