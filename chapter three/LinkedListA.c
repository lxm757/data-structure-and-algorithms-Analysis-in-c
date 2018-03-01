#include "LinkedListA.h"
#include <stdlib.h>
#include <stdio.h>

#define SpaceSize 100

enum {
   NoInitialied, Initialized
};

struct Node 
{
    ElementType Element;
    int Next;
};

struct Node CursorSpace[SpaceSize];

/* Initialize Cursor Space  */
void InitializeCursorSpace( void )
{
    int i;
    for( i = 0; i < SpaceSize; i++ )
    {
        CursorSpace[i].Next = i + 1; 
    }
    CursorSpace[i].Next = 0;
}

/* Return a new list  */
List Create( void )
{
    return Header( 0 );
}

/* Return Position of CursorSpace; 0 if CursorSpace is empty */
static Position CursorAlloc( void )
{
    Position P;
    P = CursorSpace[0].Next;
    CursorSpace[0].Next = CursorSpace[P].Next;
    return P;
}

/* free memory to CursorSpace, insert into CursorSpace  */
/* After header  */
static void CursorFree( const Position P )
{
    CursorSpace[P].Next = CursorSpace[0].Next;
    CursorSpace[0].Next = P;
}

/* Return true if L is empty  */
int IsEmpty( const List L )
{
    return CursorSpace[L].Next == 0;
}

/* Return true if P is the last position in list L  */
/* Parameter L is unused in this implementation  */
int IsLast( const Position P, const List L )
{
    return CursorSpace[P].Next == 0;
}

/* Return first value position; 0 if not exist  */
Position First( const List L )
{
    return CursorSpace[ L ].Next;
}

/* Return last value position; Header if List is empty  */
Position Last( const List L )
{
    Position P;
    P = L;
    while( !IsLast( P, L ) )
    {
        P = CursorSpace[P].Next;
    }
    return P;
}

/* Return next position of position p  */
/* Return 0 if next position is empty  */
/* Assume position p is a legal position  */
Position Advance( const Position P )
{
    return CursorSpace[ P ].Next;
}

/* Return value of position p  */
/* Assume P is a legal position  */
ElementType Retrieve( const Position P )
{
    return CursorSpace[ P ].Element;
}

/* Return Position of X in L; 0 if not found  */
Position Find( ElementType X, const List L )
{
    Position P;
    P = CursorSpace[L].Next;
    while ( P != 0 && CursorSpace[P].Element != X ){
        P = CursorSpace[P].Next;
    }
    return P;
}

/* Find X in L, insert L after header and return first position   */
Position Finds( ElementType X, const List L )
{
    Position Prev, P;
    Prev = FindPrevious( X, L );
    P = CursorSpace[ Prev ].Next;
    CursorSpace[ Prev ].Next = CursorSpace[ P ].Next;
    CursorSpace[ P ].Next = CursorSpace[ L ].Next;
    CursorSpace[ L ].Next = P;
    return P;
}

/* If X is not found, then Next field of returned  */
/* Position is 0(  */
/* Assume a header  */
Position FindPrevious( ElementType X, const List L ){
    Position P;
    P = L;
    while ( CursorSpace[P].Next != 0 &&
            CursorSpace[CursorSpace[P].Next].Element != X){
        P = CursorSpace[P].Next;
    }
    return P;
}

/* Delete first occurrence of X from a list  */
/* Assume use of a header node  */
void Delete( ElementType X, const List L ){
    Position P, TmpCell;
    P = FindPrevious( X, L );
    if ( !IsLast( P, L ) ){
        TmpCell = CursorSpace[P].Next;
        CursorSpace[P].Next = CursorSpace[TmpCell].Next;
        CursorFree( TmpCell );
    }
}

/* Return Header to List  */
/* Parameter L is unused in this implementation  */
Position Header( const List L )
{
    static int State;
    if( !State )
    {
        InitializeCursorSpace( );
        State = Initialized;
    }
    Position TmpCell;
    TmpCell = CursorAlloc( );
    if( TmpCell == 0 )
    {
        printf( "Out of space !!!" );
        exit( 1 ); /* Process stop here  */
    }
    CursorSpace[ TmpCell ].Element = 0;
    CursorSpace[ TmpCell ].Next = 0;
    return TmpCell;
}

/* Insert (after legal position P)  */
/* Header implementation assumed  */
/* Parameter L is unused in this implementation  */
void Insert( ElementType X, Position P, List L ){
    Position TmpCell;
    TmpCell = CursorAlloc( );
    if( TmpCell == 0 )
    {
        printf ( "Out of space !!!" );
        exit( 1 ); /* Process stop here  */
    }
    CursorSpace[ TmpCell ].Element = X;
    CursorSpace[ TmpCell ].Next = CursorSpace[ P ].Next;
    CursorSpace[ P ].Next = TmpCell;
}

/* Make List Empty, retain Header  */
List MakeEmpty( List L )
{
    Position P;
    while( !IsEmpty( L ) )
    {
        P = CursorSpace[L].Next;
        CursorSpace[ L ].Next = CursorSpace[ P ].Next;
        CursorFree( P );        
    }
    return L;
}

/* Delete List with header  */
void DeleteList( List L )
{
    L = MakeEmpty( L );
    CursorFree( L );
}

/* Print all emelet of List  */
void Print( const List L )
{
    Position P;
    P = L;
    while( !IsEmpty( P ) )
    {
        printf( "%d\n", 
                CursorSpace[ CursorSpace[ P ].Next ].Element );
        P = CursorSpace[ P ].Next;
    }
}
