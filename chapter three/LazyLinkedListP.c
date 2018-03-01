#include "LazyLinkedListP.h"
#include <stdlib.h>
#include <stdio.h>

///* Test  */
//int main( void )
//{
//    List L;
//    Position P;
//
//    L = Create( );
//    
//    printf( "Insert 13 at last\n" );
//    Insert( 13, Last( L ), L );
//    printf( "Insert 15 at last\n" );
//    Insert( 15, Last( L ), L );
//    printf( "Insert 17 at last\n" );
//    Insert( 17, Last( L ), L );
//    printf( "Insert 19 at last\n" );
//    Insert( 19, Last( L ), L );
//
//    printf( "Print: " );
//    Print( L );
//    putchar( '\n' );
//
//    printf( "Find 15" );
//    P = Find( 15, L );
//    if( P != NULL )
//        printf( ": %d\n" , Retrieve( P ) );
//    else
//        printf( ": Not Found\n" );
//
//    printf( "Delete 19\n" );
//    Delete( 19, L );
//
//
//    printf( "Find Deleted 19" );
//    P = Find( 19, L );
//    if( P!= NULL )
//    {
//        printf( ": %d\n", Retrieve( P ) );
//    }
//    else
//    {
//        printf( ": Not Found\n" );
//    }
//
//    printf( "Delete 13\n" );
//    Delete( 13, L );
//
//    printf( "Print: " );
//    Print( L );
//    putchar( '\n' );
//
//    printf( "DeleteList\n" );
//    DeleteList( L );
//    L = NULL; /* Avoid wild pointer  */
//
//    printf( "Print: " );
//    Print( L );
//    putchar( '\n' );
//
//    return 0;
//}

enum{ False, True };

static int DeletedCell;
static int CountedCell;
static void Clear( List );

/* Create and return a new list  */
/* Assume header used */
List Create( void )
{
    return Header( NULL );
}

/* Return a new empty list when parameter L is NULL  */
/* Otherwise make list L empty and return  */
List MakeEmpty( List L )
{
    Position P;
    if( L != NULL )
    {
        while( !IsEmpty( L ) )
        {
            /* free the first cell  */
            P = L->Next;
            L->Next = P->Next;
            free( P );
        }
    }
    return L;
}

/* Return element of position P  */
/* Assume P is a legal parameter  */
ElementType Retrieve( Position P )
{
    return P->Element;
}

/* Return true if L is empty  */
int IsEmpty( List L )
{
    if( L == NULL )
    {
        printf( "L is NULL" );
    }
    return L->Next == NULL;
}

/* Return true if P is the last cell in list L  */
/* Parameter L is unused in this implementation  */
int IsLast( Position P, List L )
{
    return P->Next == NULL;
}

/* Return next position after position P  */
/* Assume P is a legal parameter  */
/* Parameter L is unused in this implemetation  */
Position Next( Position P, List L )
{
    while( P->Next != NULL && !P->Next->IsDeleted )
    {
        P = P->Next;
    }
    return P->Next;
}

/* Return Position of X in L  */
/* Null if not found  */
/* Assume use of header node  */
Position Find( ElementType X, List L )
{
    Position P;
    P = L->Next;
    while( P != NULL )
    {
        if( !P->IsDeleted && P->Element == X ){
            break;
        }
        P = P->Next;
    }
    return P;
}

/* Return position of the first cell  */
/* Return header if list is empty  */
/* Assume L is not NULL  */
Position First( List L )
{
    while( L->Next != NULL && L->Next->IsDeleted )
    {
        L = L->Next;
    }
    return L->Next;
}

/* Return position of the last cell  */
/* Return header if list L is empty  */
Position Last( List L )
{
    Clear( L );
    while( L->Next != NULL )
    {
        L = L->Next;
    }
    return L;
}

/* Delete cell after the position P */
/* Assume P is a legal position  */
static void DeleteAfterPosition( Position P, List L )
{
    Position TmpCell;
    if( P != NULL && L != NULL ){
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        free( TmpCell );
    }
}

/* Delete cells if cell delete flag is true  */
static void Clear( List L )
{
    Position P, Prev;

    Prev = L;
    /* Go through list  */
    while( Prev->Next != NULL)
    {
        P = Prev->Next;

        if( P->IsDeleted )
        {
            /* Do not move Prev when deleted cell after Prev  */
            DeleteAfterPosition( Prev, L );
        }
        else
        {
            /* Move Prev while no deleted happened  */
            Prev = Prev->Next;
        }
    }
}

/* Lazy delete  */
/* Use a extra bit to record  */
/* wheather a cell is deleted or not  */
/* When number of lazy deleted cell   */
/* is more than half of total cells  */
/* use noraml delete function to delete them  */
void Delete( ElementType X, List L )
{
    Position P;
    P = Find( X, L );
    P->IsDeleted = True;
    DeletedCell++;
    CountedCell--;
    if( DeletedCell >= CountedCell )
    {
        Clear( L );
        DeletedCell = 0;
    }
}

/* Delete list  */
/* This function may cause a wild pointer  */
void DeleteList( List L )
{
    L = MakeEmpty( L );
    free( L );
}

/* If X is not found, then Next field of returned  */
/* position is NULL  */
/* Assume a header used  */
Position FindPrevious( ElementType X, List L )
{
    Position P;
    P = L;
    while( P->Next != NULL && P->Next->Element != X )
    {
        P = P->Next;
    }
    return P;
}

/* Insert (after legal position P)  */
/* Header implementation assumed  */
/* Parameter L is ununsed in this implementation  */
/* Assume P is a legal position  */
void Insert( ElementType X, Position P, List L )
{
    Position TmpCell;
    TmpCell = ( Position )malloc( 
            sizeof( struct Node ) );
    if( TmpCell == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    TmpCell->Element = X;
    TmpCell->IsDeleted = False;
    
    TmpCell->Next = P->Next;
    P->Next = TmpCell;

    CountedCell ++;
}

/* Create header for list L  */
/* Header implemetation assumed  */
/* Parameter L is unused in this implementation  */
Position Header( List L )
{
    Position P;
    P = ( List )malloc( sizeof( struct Node ) );
    if( P == NULL )
    {
        printf( "Out of space!!!" );
        exit( 1 );
    }
    P->Element = 0;
    P->IsDeleted = False;
    P->Next = NULL;
    
    return P;
}

/* Print all elements from list L  */
void Print( List L )
{
    while( L != NULL && !IsEmpty( L ) )
    {
        if( !L->Next->IsDeleted ){
            printf( "%d ", L->Next->Element );
        }
        L = L->Next;
    }
}

