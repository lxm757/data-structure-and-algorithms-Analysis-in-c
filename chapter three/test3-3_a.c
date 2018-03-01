#include <stdio.h>
#include <stdlib.h>
#include "LinkedListP.h"

/* Test for test  */
int main( void )
{
    void SwapWithNext( Position BeforeP, List L );
    List L;
    L = Create( );
    Insert( 13, Last( L ), L );
    Insert( 15, Last( L ), L );
    Insert( 17, Last( L ), L );

    Position P;
    P = Find( 11, L );
    SwapWithNext( P, L );

    Print( L );
    
    DeleteList( L );
    return 0;
}

/* Swap two cells for singly lists  */
/* BeforeP is the cell before the two adjacent cells 
 * that to be swaped */
void SwapWithNext( Position BeforeP, List L )
{
    Position P, AfterP;
    
    if( L != NULL && BeforeP != NULL 
            && ( P = BeforeP->Next ) != NULL
            && ( AfterP = P->Next ) != NULL )
    {
        P->Next = AfterP->Next;
        BeforeP->Next = AfterP;
        AfterP->Next = P;
    }
}


