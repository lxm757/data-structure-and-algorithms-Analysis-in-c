#include "LinkedListP.h"
#include <stdio.h>

/* Test  */
int main( void )
{
    List Union( List, List );
    List L1;
    List L2;
    L1 = Create( );
    L2 = Create( );

    Insert( 11, Last( L1 ), L1 );
    Insert( 13, Last( L1 ), L1 );
    Insert( 15, Last( L1 ), L1 );
    Insert( 17, Last( L1 ), L1 );
    Insert( 19, Last( L1 ), L1 );
    Insert( 21, Last( L1 ), L1 );

    Print( L1 );
    printf( "\n" );

    Insert( 7, Last( L2 ), L2 );
    Insert( 9, Last( L2 ), L2 );
    Insert( 11, Last( L2 ), L2 );
    Insert( 13, Last( L2 ), L2 );
    Insert( 15, Last( L2 ), L2 );
    Insert( 17, Last( L2 ), L2 );

    Print( L2 );
    printf( "\n" );

    List L3;
    L3 = Union( L1, L2 );
    Print( L3 );

    DeleteList( L1 );
    DeleteList( L2 );

    return 0;
}

/* This code can be made more abstract by using operations such as
 * Retrieve and IsPastEnd to replace L1Pos->Element and L1Pos != NULL
 * We have avoided this because operations were not rigorously defined  */
List Union( List L1, List L2 )
{
    List Result;
    Position L1Pos, L2Pos, ResultPos;
    L1Pos = First( L1 );
    L2Pos = First( L2 );
    Result = MakeEmpty( NULL );
    ResultPos = First( Result );
    while( L1Pos != NULL && L2Pos != NULL )
    {
        if( Retrieve( L1Pos ) < Retrieve( L2Pos ) )
        {
            Insert( Retrieve( L1Pos ), ResultPos, Result );
            L1Pos = Next( L1Pos, L1 );
        } 
        else if( Retrieve( L1Pos ) > Retrieve( L2Pos ) )
        {
            Insert( Retrieve( L2Pos ), ResultPos, Result );
            L2Pos = Next( L2Pos, L2 );
        }
        else
        {
            Insert( Retrieve( L1Pos ), ResultPos, Result );
            L1Pos = Next( L1Pos, L1 );
            L2Pos = Next( L2Pos, L2 );
        }
        ResultPos = Next( ResultPos, Result );
    }
    if( L2Pos != NULL )
    {
        while( L2Pos != NULL )
        {
            Insert( Retrieve( L2Pos ), ResultPos, Result );
            L2Pos = Next( L1Pos, L2 );
            ResultPos = Next( ResultPos, Result );
        }
    }
    else if( L1Pos != NULL )
    {
        while( L1Pos != NULL )
        {
            Insert( Retrieve( L1Pos ), ResultPos, Result );
            L1Pos = Next( L1Pos, L1 );
            ResultPos = Next( ResultPos, Result );
        }
    }
    return Result;
}
