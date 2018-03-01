#include "StackA.h"
#include <stdlib.h>
#include <stdio.h>

/* Stack implementation is a dynamically allocated array  */
#define EmptyTOS ( -1 ) /* Empty TopOfStack  */
#define MinStackSize ( 5 ) /* Min Size of Stack  */

struct StackRecord
{
    int Capacity; /* Stack Size  */
    int TopOfStack; /* Top Element Cursor  */
    ElementType *Array; /* Pointer to Array Store Element  */
};

/* Create a Stack, use Array  */
Stack CreateStack( int MaxElements )
{
    Stack S;

    if( MaxElements < MinStackSize )
    {
        printf( "Stack size is too small" ); /* Should stoped here  */
    }

    S = ( Stack )malloc( sizeof( struct StackRecord ) );
    if( S == NULL )
    {
        printf( "Out of space !!!" ); /* Should stoped here  */
    }
    
    S->Array = ( ElementType * )
        malloc( sizeof( ElementType ) * MaxElements );
    if( S->Array == NULL )
    {
        printf( "Out of space !!!"); /* Should stop here  */
    }
    S->Capacity = MaxElements;
    MakeEmpty( S );

    return S;
}

/* Dispose Stack  */
void DisposeStack( Stack S )
{
    if( S != NULL )
    {
        free( S->Array );
        free( S );
    }
}

/* Is Stack Empty  */
int IsEmpty( Stack S )
{
    if( S == NULL )
    {
        printf( "Must use CreateStack first" ); /* Should stop here  */
        return 0; /* This Return value used to avoid warning  */
    }
    return S->TopOfStack == EmptyTOS;
}

/* Make Stack Empty  */
void MakeEmpty( Stack S )
{
    if ( S == NULL )
    {
        printf( "Must use CreateStack first" ); /* Should stop here  */
    }
    S->TopOfStack = EmptyTOS;
}

/* Push Element into Stack  */
void Push( ElementType X, Stack S )
{
    if( IsFull( S ) )
    {
        printf( "Full Stack" );
    }
    else 
    {
        S->Array[ ++S->TopOfStack ] = X;
    }
}

/* Retuen Value of Top Stack  */
ElementType Top( Stack S )
{
    if( !IsEmpty( S ) )
    {
        return S->Array[S->TopOfStack];
    }
    printf( "Empty Stack" ); /* Should stop here  */
    return 0; /* This Return value used to avoid warning  */
}

/* Remove Top Element of Stack  */
void Pop( Stack S )
{
    if( IsEmpty( S ) )
    {
        printf( "Empty Stack" );
    }
    else 
    {
        S->TopOfStack--;
    }
}

/* Return Value of Top Stack, then Remove it  */
ElementType TopAndPop( Stack S ){
    if( !IsEmpty( S ) )
    {
        return S->Array[ S->TopOfStack-- ];
    }
    printf( "Empty Stack" ); /* Should stop here  */
    return 0; /* This Return vuale used to avoid warning  */
}
