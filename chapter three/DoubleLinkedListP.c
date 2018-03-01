#include "DoubleLinkedListP.h"
#include <stdlib.h>
#include <stdio.h>

///* Test  */
//int main( void )
//{
//    DList L = NULL;
//    L = Create( L );
//
//    L = Insert( 12, Last( L ), L );
//    L = Insert( 14, Last( L ), L );    
//    L = Insert( 16, Last( L ), L );
//
//    Print( L );
//
//    L = MakeEmpty( L );
//    printf( "%d\n", L == NULL );
//
//    Print( L );
//
//    return 0;
//}

/* Create and Return List  */
/* Parameter L is unused in this implementation  */
DList Create( DList L )
{
    if( L != NULL )
    {
        printf( "List already exist" );
        return L;
    }
    return NULL;
}

/* Return true if L is empty  */
int IsEmpty( DList L )
{
    return L == NULL;
}

/* Return true if P is last value  */
/* Parameter L is unused in this implementation  */
int IsLast( Position P, DList L )
{
    if( P != NULL && L != NULL )
    {
        return P->Next == NULL;
    }
    return 0;
}

/* Return true if P is first value  */
int IsFirst( Position P, DList L )
{
    if ( P != NULL && L != NULL )
    {
        return L == P;
    }
    return 0;
}

/* Return Position of X in L; NULL if not found  */
Position Find( ElementType X, DList L )
{
    while( L != NULL && L->Element != X )
    {
        L = L->Next;
    }
    return L;
}

/* Return Position of first value */
/* Return NULL if List is empty  */
Position First( DList L )
{
    return L;
}

/* Return Position of Last value  */
/* Return NULL if List is empty  */
Position Last( DList L )
{
    Position P;
    P = L;
    if( P != NULL )
    {
        while( !IsLast( P, L ) )
        {
            P = P->Next;
        }
    }
    return P;
}

/* Delete first occurence of X from a list  */
DList Delete( ElementType X, DList L )
{
    Position P, TmpCell;
    P = Find( X, L );

    if( P != NULL && !IsFirst( P, L ) &&
            !IsLast( P, L ) )
    {
        TmpCell = P->Prev;
        P->Next->Prev = TmpCell;
        TmpCell->Next = P->Next;
        free( P );
    }
    else if( P != NULL && IsFirst( P, L ) &&
            !IsLast( P, L ) )
    {
        L = L->Next;
        L->Prev = NULL;
        free( P );
    }
    else if( P != NULL && !IsFirst( P, L ) &&
            IsLast( P, L ) )
    {
        P->Prev->Next = NULL;
        free( P );
    }
    else if( P != NULL )
    {
        L = NULL;
        free( P );
    }
    return L;
}

/* Delete List  */
static void DeleteList( DList L )
{
    Position TmpCell;
    while( !IsEmpty( L ) )
    {
        TmpCell = L;
        L = L->Next;
        free( TmpCell );
    }
}

/* Make List empty  */
DList MakeEmpty( DList L )
{
    DeleteList( L );
    return NULL;
}

/* Insert (after legal position P)  */
DList Insert( ElementType X, Position P, DList L )
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
    TmpCell->Next = TmpCell->Prev = NULL;
    if( !IsEmpty( L ) )
    {
        if( IsLast( P, L ) )
        {
            P->Next = TmpCell;
            TmpCell->Prev = P;
        }
        else
        {
            TmpCell->Next = P->Next;
            P->Next->Prev = TmpCell;
            P->Next = TmpCell;
            TmpCell->Prev = P;
        }
    }
    else 
    {
        L = TmpCell;
    }
    return L;
}

/* Print List  */
void Print( DList L )
{
    while( !IsEmpty( L ) )
    {
        printf( "%d\n", L->Element );
        L = L->Next;
    }
}
