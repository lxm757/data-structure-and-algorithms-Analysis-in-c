#ifndef _DeQueue_h

struct QueueRecord;
struct QueueNode;
typedef int ElementType;
typedef struct QueueNode *PtrToNode;
typedef struct QueueRecord * PtrToRecord;
typedef PtrToRecord DeQueue;

int IsEmpty( DeQueue );
int IsFull( DeQueue );
DeQueue CreateQueue( int );
void DisposeQueue( DeQueue );
void MakeEmpty( DeQueue );
void Enqueue(ElementType, DeQueue );
ElementType Front( DeQueue );
void Dequeue( DeQueue );
ElementType FrontAndDequeue( DeQueue );

void Push( ElementType, DeQueue );
ElementType Pop( DeQueue );
void Inject( ElementType, DeQueue );
ElementType Eject( DeQueue );

#endif
