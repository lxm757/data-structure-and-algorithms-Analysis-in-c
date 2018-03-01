#ifndef _Stack_H

struct Node;
typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmptyStack( Stack S );
Stack CreateStack( void );
void DisposeStack( Stack S );
void MakeStackEmpty( Stack S );
void Push( ElementType X, Stack S );
ElementType Top( Stack S );
ElementType TopAndPop( Stack S );
void Pop( Stack S );

#endif
