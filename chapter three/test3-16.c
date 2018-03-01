#include "LinkedListA.h"
#include <stdio.h>

/* Test  */
int main( void )
{
    void DeleteDuplicated( List L );
    List L;
    L = Create( );

    Insert( 3, Last( L ), L );
    Insert( 5, Last( L ), L );
    Insert( 7, Last( L ), L );
    Insert( 11, Last( L ), L );
    Insert( 5, Last( L ), L );
    Insert( 13, Last( L ), L );
    Insert( 3, Last( L ), L );
    Insert( 7, Last( L ), L );
    Insert( 19, Last( L ), L );
    Insert( 3, Last( L ), L );

    Print( L );
    putchar( '\n' );

    DeleteDuplicated( L );
    Print( L );
    putchar( '\n' );

    DeleteList( L );
    return 0;
}

/* Delete duplicated number  */
/* This takes O(N^2)  */
void DeleteDuplicated( List L )
{
    Position Prev, P, Next;
    ElementType Element;

    while( !IsEmpty( L ) )
    {
        P = Advance( L );
        Next = Advance( P );
        Prev = P;
        while( Next != 0 )
        {
            if( Retrieve( P ) == Retrieve( Next ) )
            {
                Element = Retrieve( Next );
                Next = Advance( Next );
                Delete( Element, Prev ); /* Only O(C)  */
            }
            else
            {
                Prev = Next;
                Next = Advance( Next );
            }

        }
        L = Advance( L );
    }
    
}

