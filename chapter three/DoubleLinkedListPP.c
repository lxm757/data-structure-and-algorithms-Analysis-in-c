#include "DoubleLinkedListPP.h"
#include <stdlib.h>
#include <stdio.h>

/* Create and return new List  */
DList Create( DList L )
{
    if( L == NULL )
    {
        L = ( DList )malloc(
                sizeof( Position ) );
        *L = NULL;
    }
    return L;
}

///* Test  */
//int main( void )
//{
//    DList L = NULL;
//    L = Create( L );
//    Insert( 13, Last( L ), L );
//    Insert( 15, Last( L ), L );
//
//    SwapWithNext( Find( 13, L ), L );
//
//    Print( L );
//    printf( "\n" );
//    PrintInReverse( L );
//    return 0;
//}

/* Is List L empty  */
int IsEmpty( DList L )
{
    Position P;
    P = L == NULL ? 
        NULL : *L;
    return P == NULL;
}

/* Return true if P is the last node  */
int IsLast( Position P, DList L )
{
    if( P != NULL && L != NULL )
    {
        return P->Next == NULL;
    }
    return 0;
}

/* Return true if P is the first node  */
int IsFirst( Position P, DList L )
{
    if( P != NULL && L != NULL )
    {
        return P->Prev == NULL;
    }
    return 0;
}

/* Return position of X in L; NULL if not found  */
Position Find( ElementType X, DList L )
{
    Position P;
    P = L == NULL ? NULL : *L;
    while( P != NULL && P->Element != X )
    {
        P = P->Next;
    }
    return P;
}

/* Return Position of first value  */
/* Return NULL if List is empty  */
Position First( DList L )
{
    return L == NULL ? 
        NULL : *L;
}

/* Return Position of last value  */
/* Return NULL if list is empty  */
Position Last( DList L )
{
    Position P;
    P = L == NULL ? NULL : *L;
    if ( P != NULL )
    {
        while( !IsLast( P, L ) )
        {
            P = P->Next;
        }
    }
    return P;
}

/* Delete first occurrence of X from a list   */
void Delete( ElementType X, DList L )
{
    /* There is a simply version
     * See function SwapWithNext below  */
    printf( "delete\n" );
    Position P, TmpCell;
    P = Find( X, L );
    if( P != NULL && !IsFirst( P, L ) &&
            !IsLast( P, L ) )
    {
        printf( "middle\n" );
        TmpCell = P->Prev;
        P->Next->Prev = TmpCell;
        TmpCell->Next = P->Next;
        free( P );
    } 
    else if( P != NULL && IsFirst( P, L ) &&
            !IsLast( P, L ) )
    {
        printf( "first\n" );
        *L = (*L)->Next;
        (*L)->Prev = NULL;
        free( P );
    }
    else if( P != NULL && !IsFirst( P, L ) &&
            IsLast( P, L ) )
    {
        printf( "last\n" );
        P->Prev->Next = NULL;
        free( P );
    }
    else if( P != NULL )
    {
        printf( "only one\n" );
        *L = NULL;
        free( P );
    }
}

/* Delete List  */
void DeleteList( DList L )
{
    MakeEmpty( L );
    free( *L );
}

/* Make List empty  */
void MakeEmpty( DList L )
{
    Position TmpCell;
    while( !IsEmpty( L ) )
    {
        TmpCell = *L;
        *L = (*L)->Next;
        free( TmpCell );
    }
}

/* Insert (after legal position P)  */
void Insert( ElementType X, Position P, DList L )
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
    else if( L != NULL )
    {
        ( *L ) = TmpCell;
    }
    else
    {
        printf( "Initialize list first" );
    }
}


/* Swap two cells for double linked lists  */
/* P and AfterP are cells to be switched  */
void SwapWithNext( Position P, DList L )
{
    /* PrevP is P->prev, AfterA is A->Next  */
    Position AfterP;
    if ( L != NULL && P != NULL 
            && ( AfterP = P->Next ) != NULL )
    {
        /* Before:
         * PrevP -> P -> AfterP -> AfterA  
         * PrevP <- P <- AfterP <- AgterA  */
        P->Next = AfterP->Next;
        AfterP->Next = P;
        if( !IsFirst( P, L ) )
        {
            P->Prev->Next = AfterP;
        }
        else 
        {
            *L = AfterP;
        }
        /* After:
         * PrevP -> AfterP -> P -> AfterA  
         * PrevP <- P <- AfterP <- AfterA*/

        /* Before:
         * PrevP -> AfterP -> P -> AfterA
         * PrevP <- P <- AfterP <- AfterA  */
        AfterP->Prev = P->Prev;
        P->Prev = AfterP;
        if( !IsLast( P, L ) )
        {
            P->Next->Prev = P;
        }
        /* After:
         * PrevP -> AfterP -> P -> AfterA
         * PrevP <- AfterP <- P <- AfterA  */
    }
}


/* Print List  */
void Print( DList L )
{
    Position P;
    if( !IsEmpty( L ) )
    {
        P = *L;
        while( !IsLast( P, L ) )
        {
            printf( "%d\n", P->Element );
            P = P->Next;
        }
        printf( "%d\n", P->Element );
    }
}

/* Print List in reverse order  */
void PrintInReverse( DList L )
{
    Position P;
    if( !IsEmpty( L ) )
    {
        P = Last( L );
        while ( !IsFirst( P, L ) )
        {
            printf( "%d\n", P->Element );
            P = P->Prev;
        }
        printf( "%d\n", P->Element );
    }
}
