#ifndef _Min_Stack_H

struct MinNode;
typedef int MinElementType;
typedef struct MinNode *MinStack;

int IsMinStackEmpty( MinStack );
MinStack CreateMinStack( void );
void DisposeMinStack( MinStack );
void MakeMinStackEmpty( MinStack );
void MinPush( MinElementType, MinStack );
MinElementType MinPop( MinStack );
MinElementType FindMin( MinStack );

#endif
