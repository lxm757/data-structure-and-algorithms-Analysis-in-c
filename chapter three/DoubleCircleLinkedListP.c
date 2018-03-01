#include "DoubleCircleLinkedListP.h"
#include <stdlib.h>
#include <stdio.h>

/* Create and return new circle list  */
DCList Create( DCList L )
{
    if( L == NULL )
    {
        L = ( DCList )malloc( 
               sizeof( Position ) ); 
        *L = NULL;
        return L;
    }
    printf( "List exist" );
    return L;
}

///* Test  */
//int main( void )
//{
//    DCList L = NULL;
//    L = Create( L );
//    Insert( 13, Last( L ), L );
//    Insert( 15, Last( L ), L );
//    Insert( 17, Last( L ), L );
//
//    Print( L );
//    printf( "\n" );
//    PrintInReverse( L );
//    printf( "\n" );
//
//    Delete( 17, L );
//    Print( L );
//    printf( "\n" );
//    PrintInReverse( L );
//    printf( "\n" );
//
//    Delete( 13, L );
//    Print( L );
//    printf( "\n" );
//    PrintInReverse( L );
//    printf( "\n" );
//    
//    Delete( 15, L );
//    Print( L );
//    printf( "\n" );
//    PrintInReverse( L );
//    printf( "\n" );
//
//    Insert( 11, Last( L ), L );
//    Insert( 13, Last( L ), L );
//
//    Print( L );
//    printf( "\n" );
//    PrintInReverse( L );
//    printf(" \n" );
//
//    DeleteList( L );
//    Print( L );
//    return 0;
//}

/* Is List empty */ 
int IsEmpty( DCList L )
{
    Position P;
    P = L == NULL ?
        NULL : *L;
    return P == NULL;
}

/* Return true if P is the last cell  */
/* What cell called the last cell in circle list ?  */
int IsLast( Position P, DCList L )
{
   if( P != NULL && L != NULL )
   {
       return P->Next == *L;
   }
   return 0;
}

/* Return true if P is the first cell  */
/* How to defined first cell ?   */
int IsFirst( Position P, DCList L )
{
    if( P != NULL && L != NULL )
    {
        return P == *L; 
    }
    return 0;
}

/* Return Position of X in L; NULL if not found  */
Position Find( ElementType X, DCList L )
{
    Position P;
    if( !IsEmpty( L ) )
    {
        P = *L;
        do
        {
            if( P->Element == X )
            {
                return P;
            }
            P = P->Next;
        }
        while( P != *L );
    }
    return NULL;
}

/* Return Position of Last cell  */
/* Return NULL if List is empty  */
Position First( DCList L )
{
    return L == NULL ?
        NULL : *L;
}

/* Return Position of last cell  */
/* Return NULL if list is empty  */
Position Last( DCList L )
{
    if( L != NULL && *L != NULL )
    {
        return (*L)->Prev;
    }
    return NULL;
}

/* Get next position of p  */
/* Assume parameter p is a legal parameter  */
Position Advance( Position P )
{
    return P == NULL ?
        NULL : P->Next;
}

/* Get previous position of p  */
/* Assume parameter p is a leagal parameter  */
Position Previous( Position P )
{
    return P == NULL ?
        NULL : P->Prev;
}

/* There are two implemetation of Delete  */
/* Compare and find differece  */

/* Delete the position cell  */
void DeletePosition( Position P, DCList L )
{
    if( P != NULL && !IsFirst( P, L ) )
    {
        P->Prev->Next = P->Next;
        P->Next->Prev = P->Prev;
        free( P );
    }
    else if( P != NULL && !IsLast( P, L ) )
    {
        *L = P->Next;
        P->Prev->Next = P->Next;
        P->Next->Prev = P->Prev;
        free( P );
    }
    else if( P != NULL )
    {
        *L = NULL;
        free( P );
    }
}

/* Delete cell at position P  */
static void DeletePositionP( Position P, DCList L )
{
    if( P != NULL )
    {
        P->Prev->Next = P->Next;
        P->Next->Prev = P->Prev;
        if( IsFirst( P, L ) )
        {
            if( IsLast( P, L ) )
            {
                *L = NULL;
            }
            else 
            {
                *L = P->Next;
            }
        }
        free( P );
    }
}

/* Delete first occurence of X from a list  */
void Delete( ElementType X, DCList L )
{
    Position P;
    P = Find( X, L );
    //printf( "Delete %d\n", P->Element );
    DeletePositionP( P, L );
}

/* Delete list  */
void DeleteList( DCList L )
{
    printf( "DeleteList\n" );
    MakeEmpty( L );
    free( *L );
}

/* Make list empty  */
void MakeEmpty( DCList L )
{
    while( !IsEmpty( L ) )
    {
        DeletePosition( *L, L );
    }
}

/* Insert (after legal positon)  */
void Insert( ElementType X, Position P, DCList L )
{
    Position TmpCell;
    TmpCell = ( Position )malloc( 
           sizeof( struct Node ) );

    TmpCell->Element = X;
    TmpCell->Next = TmpCell->Prev = TmpCell;
    if( !IsEmpty( L ) )
    {
        TmpCell->Next = P->Next;
        P->Next = TmpCell;
        TmpCell->Next->Prev = TmpCell;
        TmpCell->Prev = P;
    }
    else if( L != NULL )
    {
        *L = TmpCell;
    }
    else 
    {
        printf( "Initialize list first" );
    }
}

/* Get element of position p  */
/* Assume parameter is a legal parameter  */
ElementType Retrieve( Position P )
{
    return P->Element;
}

/* Print list  */
void Print( DCList L )
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

/* Print list in reverse order  */
void PrintInReverse( DCList L )
{
    Position P;
    if( !IsEmpty( L ) )
    {
        P = Last( L );
        while( !IsFirst( P, L ) )
        {
            printf( "%d\n", P->Element );
            P = P->Prev;
        }
        printf( "%d\n", P->Element );
    }
}
