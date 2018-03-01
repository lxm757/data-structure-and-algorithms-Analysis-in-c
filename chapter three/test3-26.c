#include "test3-26.h"
#include <stdlib.h>
#include <stdio.h>

struct QueueRecord
{
    int Capacity;
    int Size;
    PtrToNode Front;
    PtrToNode Rear;
};

struct QueueNode
{
    ElementType Element;
    PtrToNode Next;
};


///* Test  */
//int main( void )
//{
//    Queue Q;
//    Q = CreateQueue( 10 );
//
//    Enqueue( 19, Q );
//    Enqueue( 13, Q );
//    Enqueue( 11, Q );
//    Enqueue( 15, Q );
//    Enqueue( 17, Q );
//
//    ElementType Element;
//    Element = FrontAndDequeue( Q );
//    printf( "%d\n", Element );
//    Element = FrontAndDequeue( Q );
//    printf( "%d\n", Element );
//    Element = FrontAndDequeue( Q );
//    printf( "%d\n", Element );
//
//
//    DisposeQueue( Q );
//
//    return 0;
//}


/* Create and return a new queue wiht header  */
DeQueue CreateQueue( int MaxElements )
{
    DeQueue Q;
    PtrToNode Node;
    Q = ( DeQueue )malloc(
            sizeof( struct QueueRecord ) );
    Node = ( PtrToNode )malloc(
            sizeof( struct QueueNode ) );
    if( Q == NULL || Node == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }

    Node->Element = 0;
    Node->Next = NULL;

    Q->Front = Q->Rear = Node;
    Q->Capacity = MaxElements;
    Q->Size = 0;

    return Q;
}

/* Is queue empty  */
int IsEmpty( DeQueue Q )
{
    return Q->Front->Next == NULL;
}

/* Is queue full  */
int IsFull( DeQueue Q )
{
    return Q->Size >= Q->Capacity;
}

/* Make queue empty  */
void MakeEmpty( DeQueue Q )
{
    PtrToNode P;
    while( !IsEmpty( Q ) )
    {
        P = Q->Front->Next;
        Q->Front->Next = P->Next;
        free( P );
    }
    Q->Rear = Q->Front;
}

/* Dispose queue  */
void DisposeQueue( DeQueue Q )
{
    MakeEmpty( Q );
    free( Q );
}

/* Put a vule into queue  */
void Enqueue( ElementType X, DeQueue Q )
{
    PtrToNode P;
    P = ( PtrToNode )malloc( 
            sizeof( struct QueueNode ) );
    if( P == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }

    P->Element = X;
    P->Next = NULL;

    Q->Rear->Next = P;
    Q->Rear = P;

    Q->Size++;
}

/* Return value of front cell  */
ElementType Front( DeQueue Q )
{
    if( !IsEmpty( Q ) )
    {
        return Q->Front->Next->Element;
    }
    printf( "Empty Queue" );
    return 0; /* This 0 used to avoid warning  */
}

/* Remove fisrt cell from queue  */
void Dequeue( DeQueue Q )
{
    PtrToNode P;
    P = Q->Front->Next;
    Q->Front->Next = P->Next;
    if( IsEmpty( Q ) )
    {
        Q->Rear = Q->Front;
    }
    Q->Size--;
}

/* Return value of first cell and remove it  */
ElementType FrontAndDequeue( DeQueue Q )
{
    ElementType Element;
    Element = Front( Q );
    Dequeue( Q );
    Q->Size--;
    return Element;
}

/* Push value into front  */
void Push( ElementType X, DeQueue Q )
{
    PtrToNode P;
    P = ( PtrToNode )malloc(
            sizeof( struct QueueNode ) );
    if( P == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    P->Element = X;

    P->Next = Q->Front->Next;
    Q->Front->Next = P;
    Q->Size++;
}

/* Return value of front cell and remove it  */
ElementType Pop( DeQueue Q )
{
    ElementType Element;
    PtrToNode P;
    if( !IsEmpty( Q ) )
    {
        P = Q->Front->Next;
        Element = P->Element;
        Q->Front->Next = P->Next;
        free( P );
        return Element;
    }
    printf( "DeQueue Empty" );
    return 0; /* This 0 used to avoid warning  */
}

/* Inject  */
void Inject( ElementType X, DeQueue Q )
{
    Enqueue( X, Q);
}

/* Eject  */
ElementType Eject( DeQueue Q )
{
    return FrontAndDequeue( Q );
}


