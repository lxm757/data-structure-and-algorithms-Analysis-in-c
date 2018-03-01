#include "LinkedListP.h"
#include <stdio.h>
#include <stdlib.h>

/* Test  */
int main( void )
{
    List ReverseList( List L );
    List ReverseListRecursively( List L );
    List ReverseListWithStack( List L );

    List L = NULL;
    L = Create( );

    Insert( 13, Last( L ), L );
    Insert( 15, Last( L ), L );
    Insert( 17, Last( L ), L );

    Print( L );
    putchar( '\n' );

    L = ReverseListWithStack( L );
    Print( L );
    putchar( '\n' );

    DeleteList( L );

    return 0;
}

/* Reversal of a singly linked list done with recursively  */
/* Assume no header and L is not empty  */
/* List with header usage:   */
/* L->Next = ReverseListRecursively( L->Next )  */
List ReverseListRecursively( List L )
{
    Position P;
    if( L->Next == NULL )
    {
        return L;
    }
    P = L;
    L = ReverseListRecursively( L->Next );
    Last( L )->Next = P;
    P->Next = NULL;
    return L;
}


/* Reversal of a singly linked list can be done  */
/* Nonrecursively by using a stack, but this requires O(N)  */
/* Extra space.  */
/* Assume header and L is not empty  */
List ReverseListWithStack( List L )
{
    List Tmp;
    Position P, TmpP;

    Tmp = Create( );
    TmpP = Tmp;

    while( L->Next != NULL )
    {
        P = L->Next;    
        L->Next = P->Next;
        P->Next = TmpP->Next; 
        TmpP->Next = P;
    }
    return Tmp;
}

/* The following solution is similar to strategies employed  */
/* in garbge collection algorithms.  */
/* At the top of the while loop, the list from the start to  */
/* PreviousPos is already reversed, whereas the rest of the list  */
/* From CurrentPos to the end, is normal.  */
/* This alogrithm uses only constant extra space  */

/* Assuming header and L is not empty  */
List ReverseList( List L )
{
    Position CurrentPos, NextPos, PreviousPos;
    PreviousPos = NULL;
    CurrentPos = L->Next;
    NextPos = CurrentPos->Next;
    while( NextPos != NULL )
    {
        CurrentPos->Next = PreviousPos;
        PreviousPos = CurrentPos;
        CurrentPos = NextPos;
        NextPos = NextPos->Next;
    }
    CurrentPos->Next = PreviousPos;
    L->Next = CurrentPos;
    return L;
}
