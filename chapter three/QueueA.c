#include "QueueA.h"
#include <stdlib.h>
#include <stdio.h>

#define MinQueueSize ( 5 )

/* Queue implentation is a dynamically allocated array  */
struct QueueRecord
{
    int Capacity;
    int Size;
    int Front; /* Pointer to front  */
    int Rear; /* Pointer to rear  */
    ElementType *Array;
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
//    Element = FrontAndDequeue( Q );
//    printf( "%d\n", Element );
//
//    return 0;
//}

/* Create and return a new queue  */
Queue CreateQueue( int MaxElements )
{
    MaxElements = MaxElements > MinQueueSize ? 
        MaxElements : MinQueueSize;
    Queue Q;
    ElementType *Arr;
    Q = ( Queue )malloc( 
            sizeof( struct QueueRecord ) );
    Arr = ( ElementType * )malloc(
            sizeof( MaxElements ) );
    if( Q == NULL || Arr == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    
    Q->Capacity = MaxElements;
    Q->Size = 0;
    Q->Front = 0;
    Q->Rear = Q->Front - 1;
    Q->Array = Arr;

    return Q;
}

/* Is Queue Empty  */
int IsEmpty( Queue Q )
{
    return Q->Size == 0;
}

/* Is Queue Full  */
int IsFull( Queue Q ){
    /* can also use:  */
    /* Q->Rear == Q->Front - 1  */
    return Q->Size == Q->Capacity; 
}

/* Make Queue Empty  */
void MakeEmpty( Queue Q )
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

/* Reset pointer to begin if pointer is more
 * than capacity  */
static int Succ( int Value, Queue Q )
{
    if( ++Value == Q->Capacity )
    {
        return 0;
    }
    return Value;
}

/* Put a value into queue  */
void Enqueue( ElementType X, Queue Q )
{
    if( IsFull( Q ) ){
        printf( "Full Queue" );
    }
    else 
    {
        Q->Size++;
        Q->Rear = Succ( Q->Rear, Q );
        Q->Array[ Q->Rear ] = X;
    }
}

/* Return a value from queue  */
ElementType Front( Queue Q )
{
    if( !IsEmpty( Q ) )
    {
        return Q->Array[ Q->Front ];
    }
    else 
    {
        printf( "Queue empty" );
        return 0; /* This 0 used to avoid warning  */
    }
}

/* Dequeue a value  */
void Dequeue( Queue Q )
{
    Q->Size--;
    Q->Front = Succ( Q->Front, Q );
}

/* Return value from queue and delete it  */
ElementType FrontAndDequeue( Queue Q )
{
    ElementType X;
    X = Front( Q );
    Dequeue( Q );
    return X;
}

/* Dispose queue  */
void DisposeQueue( Queue Q )
{
    free( Q->Array );    
    free( Q );
}
