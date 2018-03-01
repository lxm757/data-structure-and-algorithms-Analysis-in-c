#include "StackP.h"
#include <stdlib.h>
#include <stdio.h>

/* Stack implementation is a linked list with a header  */
struct Node
{
    ElementType Element;
    PtrToNode Next;
};

/* Is a Stack Empty  */
int IsEmptyStack( Stack S )
{
    return S->Next == NULL;
}

/* Create a new Stack with header, return a Pointer to Header  */
Stack CreateStack( void )
{
    Stack S;
    S = ( Stack )malloc( sizeof( struct Node ) );
    if ( S == NULL ) 
    {
        printf( "Out of space !!!" );
    }
    S->Next = NULL;
    MakeStackEmpty( S ); 
    return S;
}

/* Make Stack empty  */
void MakeStackEmpty( Stack S )
{
    if ( S == NULL )
    {
        printf( "Must use CreateStack first" );
    } 
    else 
    {
        while( !IsEmptyStack( S ) )
        {
            Pop( S );
        }
    }
}

/* Push a Element into Stack  */
/* Assume stack is a legal stack  */
void Push( ElementType X, Stack S )
{
    PtrToNode TmpCell;
    TmpCell = ( PtrToNode )malloc( sizeof( struct Node) );
    if( TmpCell == NULL) 
    {
        printf( "Out of space !!!" );
    }
    else 
    {
        TmpCell->Element = X;
        TmpCell->Next = S->Next;
        S->Next = TmpCell;
    }
}

/* Retuen value of first Node from Stack  */
ElementType Top( Stack S ){
    if( !IsEmptyStack( S ) )
    {
        return S->Next->Element;
    }
    printf( "Empty stack" ); /* Process should stop here  */
    return 0; /* This Return value used to avoid warning  */
}

/* Pop Node from Stack  */
void Pop( Stack S )
{
    PtrToNode FirstCell;
    if( IsEmptyStack( S ) ){
        printf( "Empty Stack" );
    }
    else 
    {
        FirstCell = S->Next;
        S->Next = FirstCell->Next;
        free( FirstCell );
    }
}

/* Top and Pop from Stack  */
ElementType TopAndPop( Stack S )
{
    ElementType TmpCell;
    TmpCell = Top( S );
    Pop( S );
    return TmpCell;
}

/* Dispose stack  */
void DisposeStack( Stack S )
{
    while( !IsEmptyStack( S ) )
    {
        Pop( S );
    }    
    free( S );
}
