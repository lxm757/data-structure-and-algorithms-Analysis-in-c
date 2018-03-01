#include "QueueP.h"
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
Queue CreateQueue( int MaxElements )
{
    Queue Q;
    PtrToNode Node;
    Q = ( Queue )malloc(
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
int IsEmpty( Queue Q )
{
    return Q->Front->Next == NULL;
}

/* Is queue full  */
int IsFull( Queue Q )
{
    return Q->Size >= Q->Capacity;
}

/* Make queue empty  */
void MakeEmpty( Queue Q )
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
void DisposeQueue( Queue Q )
{
    MakeEmpty( Q );
    free( Q );
}

/* Put a vule into queue  */
void Enqueue( ElementType X, Queue Q )
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
}

/* Return value of front cell  */
ElementType Front( Queue Q )
{
    if( !IsEmpty( Q ) )
    {
        return Q->Front->Next->Element;
    }
    printf( "Empty Queue" );
    return 0; /* This 0 used to avoid warning  */
}

/* Remove fisrt cell from queue  */
void Dequeue( Queue Q )
{
    PtrToNode P;
    P = Q->Front->Next;
    Q->Front->Next = P->Next;
    if( IsEmpty( Q ) )
    {
        Q->Rear = Q->Front;
    }
}

/* Return value of first cell and remove it  */
ElementType FrontAndDequeue( Queue Q )
{
    ElementType Element;
    Element = Front( Q );
    Dequeue( Q );
    return Element;
}

