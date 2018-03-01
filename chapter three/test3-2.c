#include "LinkedListP.h"
#include <stdio.h>

int main( void )
{
    void PrintInOrder( List, List );
    List L = NULL;
    L = Header( L );
    Insert( 13, Last( L ), L );
    Insert( 15, Last( L ), L );
    Insert( 17, Last( L ), L );
    Insert( 19, Last( L ), L );
    Insert( 21, Last( L ), L );
    Print( L );

    List P = NULL;
    P = Header( P );
    Insert( 1, Last( P ), P );
    Insert( 3, Last( P ), P );
    Insert( 5, Last( P ), P );
    Print( P );

    PrintInOrder( L, P );

    DeleteList( L );

    return 0;
}

void PrintInOrder( List L, List P )
{
    int Counter;
    Position Lpos, Ppos;
    /* Skip header  */
    Lpos = L->Next;
    Ppos = P->Next;
    
    Counter = 1;
    while( Lpos != NULL && Ppos != NULL )
    {
        if( Ppos->Element == Counter++ )
        {
            printf( "%d\n", Lpos->Element );
            Ppos = Ppos->Next;
        }
        Lpos = Lpos->Next;
    }
}
