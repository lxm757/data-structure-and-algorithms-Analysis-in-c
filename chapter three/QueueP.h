#ifndef _Queue_h

struct QueueRecord;
struct QueueNode;
typedef int ElementType;
typedef struct QueueNode *PtrToNode;
typedef struct QueueRecord * PtrToRecord;
typedef PtrToRecord Queue;

int IsEmpty( Queue );
int IsFull( Queue );
Queue CreateQueue( int );
void DisposeQueue( Queue );
void MakeEmpty( Queue );
void Enqueue( ElementType, Queue );
ElementType Front( Queue );
void Dequeue( Queue );
ElementType FrontAndDequeue( Queue );

#endif
