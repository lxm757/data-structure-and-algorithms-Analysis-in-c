#include "test3-22.h"
#include "StackP.h"
#include <stdlib.h>
#include <stdio.h>

struct MinNode
{
    Stack S;
    Stack M;
};

///* Test  */
//int main( void )
//{
//    MinStack MS;
//    MS = CreateMinStack( );
//
//    MinPush( 17, MS );
//    MinPush( 11, MS );
//    MinPush( 15, MS );
//    MinPush( 13, MS );
//
//    printf( "Min: %d\n", FindMin( MS ) );
//
//    return 0;
//}

/* Is a Stack Empty  */
int IsMinStackEmpty( MinStack MS )
{
    return IsEmptyStack( MS->S );
}

/* Create a new stack with header, return a Pointer to Header  */
MinStack CreateMinStack( void )
{
    MinStack MS;
    MS = ( MinStack )malloc(
            sizeof( struct MinNode ) );
    if( MS == NULL )
    {
        printf( "Out of space !!!" );
    }
    Stack S = CreateStack( );
    Stack M = CreateStack( );
    MS->S = S;
    MS->M = M;
    return MS;  
}

void MakeMinStackEmpty( MinStack MS )
{
    if( MS == NULL )
    {
        printf( "Must use CreateMinStack first" );
    }
    else
    {
        while( !IsEmptyStack( MS->S ) )
        {
            MinPop( MS );
        }
    }
}

/* Push a element into stack  */
void MinPush( MinElementType X, MinStack MS )
{
    if( IsMinStackEmpty( MS ) )
    {
        Push( X, MS->S );
        Push( X, MS->M );
    }
    else 
    {
        Push( X, MS->S );
        if( X < Top( MS->M ) )
        {
            Push( X, MS->M );
        }
    }
}

/* Pop node from stack  */
MinElementType MinPop( MinStack MS )
{
    MinElementType X;
    X = TopAndPop( MS->S );
    if( X == Top( MS->M ) )
    {
        Pop( MS->M );
    }
    return X;
}

/* Find min  */
MinElementType FindMin( MinStack MS )
{
    return Top( MS->M );
}

/* Dispose stack  */
void DisposeMinStack( MinStack MS )
{
    MakeMinStackEmpty( MS );
    free( MS );
}

