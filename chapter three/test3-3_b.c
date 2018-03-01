#include "DoubleLinkedListPP.h"
#include <stdio.h>

/* Test  */
int main( void )
{
    void SwapWithNext( Position P, DList L );
    DList L = NULL;
    L = Create( L );
    Insert( 17, Last( L ), L );
    Insert( 19, Last( L ), L );
    Print( L );
    printf( "\n" );
    PrintInReverse( L );

    SwapWithNext( Find( 17, L ), L );
    printf( "Switch\n" );

    Print( L );
    printf("\n");
    PrintInReverse( L );

    DeleteList( L );

    return 0;
}

/* Swap two cells for double linked lists  */
/* P and AfterP are cells to be switched  */
/* See DoubleLinkedListPP.c for a simply version  */
void SwapWithNext( Position P, DList L )
{
    Position AfterP;

    if( L != NULL && P != NULL 
           && ( AfterP = P->Next ) != NULL )
    {
        if( !IsFirst( P, L ) && !IsLast( AfterP, L ) )
        {
            printf( "Middle\n" );
            P->Next = AfterP->Next;
            AfterP->Next = P;
            P->Prev->Next = AfterP; 
            P->Next->Prev = P;
            AfterP->Prev = P->Prev;
            P->Prev = AfterP;
        }
        else if( IsFirst( P, L ) && !IsLast( AfterP, L ) )
        {
            printf( "First\n" );
            P->Next = AfterP->Next;
            AfterP->Next = P;
            P->Next->Prev = P;
            AfterP->Prev = P->Prev;
            P->Prev = AfterP;
            *L = AfterP;
        }
        else if( !IsFirst( P, L ) && IsLast( AfterP, L ) )
        {
            printf( "Last\n" );
            P->Next = AfterP->Next;
            AfterP->Next = P;
            P->Prev->Next = AfterP;
            AfterP->Prev = P->Prev;
            P->Prev = AfterP;
        }
        else 
        {
            printf( "Only two\n" );
            P->Next = AfterP->Next;
            AfterP->Next = P;
            AfterP->Prev = P->Prev;
            P->Prev = AfterP;
            *L = AfterP;
        }
    } 
}
