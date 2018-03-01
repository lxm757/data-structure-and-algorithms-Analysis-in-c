#include "LinkedListP.h"
#include <stdlib.h>
#include <stdio.h>

/* Create and Return a list with header  */
List Create( void )
{
    return Header( NULL );
}

/* Do nothing and return NULL if parameter L is NULL  */
/* Otherwise make list L empty and return l  */
List MakeEmpty( List L )
{
    Position P;
    if( L == NULL )
    {
        return L; 
    }    
    /* Delete cells expect for header  */
    while( !IsEmpty( L ) )
    {
        P = L->Next;
        L->Next = P->Next;
        free( P );
    }
    return L;
}

/* Return Element of Position P  */
/* Assume P is a legal parameter  */
ElementType Retrieve( Position P )
{
    return P->Element;
}

/* Return true if L is empty  */
int IsEmpty( List L )
{
    return L->Next == NULL;
}

/* Return true if P is the last position in list L  */
/* Parameter L is unused in this implementation  */
int IsLast( Position P, List L )
{
    return P->Next == NULL;
}

/* Return next position after posiiton p  */
/* Assume P is a legal parameter  */
Position Next( Position P, List L )
{
    if( L != NULL && P != NULL )
    {
        return P->Next;
    }
    return NULL;
}
/* Return Position of X in L; NULL if not found  */
/* assume use of header node   */
Position Find( ElementType X, List L )
{
    Position Prev, P;
    Prev = FindPrevious( X, L );
    P = NULL;
    if( !IsLast( Prev, L ) )
    {
        P = Prev->Next;
        Prev->Next = P->Next;
        P->Next = L->Next;
        L->Next = P;
    }
    return P;
}

/* Return Position of the first element  */
/* Return header if list is empty  */
/* Assume L is not NULL  */
Position First( List L )
{
    if( L->Next != NULL )
    {
        return L->Next;
    }
    return L;
}

/* Return Position of the last cell in List */
/* Return Hedaer if List is empty  */
Position Last( List L )
{
    while( L->Next != NULL )
    {
        L = L->Next;
    }
    return L;
}

/* Delete first occurence of X from a list  */
/* assume use of header node  */
void Delete( ElementType X, List L )
{
    Position P, TmpCell;
    P = FindPrevious( X, L );
    if( !IsLast( P, L ) )
    {     /* Assumption of header use  */
        /* X is found; delete it  */
        TmpCell = P->Next;
        P->Next = TmpCell->Next; /* Bypass deleted cell  */
        free( TmpCell );
    }
}

/* Delete List  */
void DeleteList( List L )
{
    Position P;
    while( !IsEmpty( L ) )
    {
        P = L->Next;
        L->Next = P->Next;
        free( P );
    }
    free ( L );
}

/* If X is not found, then Next field of returned
 * Position is NULL  */
/* Assumes a header used  */
Position FindPrevious( ElementType X, List L )
{
    Position P;
    P = L;
    while ( P->Next != NULL && P->Next->Element != X )
    {
        P = P->Next;
    }
    return P;
}

/* Insert (after legal position P)  */
/* Header implementation assumed  */
/* Parameter L is unused in this implementation  */
void Insert( ElementType X, Position P, List L )
{
    Position TmpCell;
    TmpCell = ( Position )malloc(sizeof( struct Node ));
    if( TmpCell == NULL ){
        printf ( "Out of space !!!" );
        exit( 1 );
    }
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

/* Create header for List  */
/* Header implementation assumed  */
/* Parameter L is unused in this implementation  */
Position Header( List L )
{
    Position P;
    P = ( List )malloc( sizeof( struct Node ) );
    if( P == NULL )
    {
        printf( "Can't allocated" );
    }
    P->Element = 0;
    P->Next = NULL;
    return P;
}


/* Print all elements from List  */
void Print( List L )
{
    Position P;
    P = L;
    while( !IsEmpty( P ) )
    {
        printf( "%d ", P->Next->Element );
        P = P->Next;
   }
}

/* Swap two cells for singly lists  */
/* BeforeP is the cell before the two adjacent 
 * cells that to be swaped  */
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
