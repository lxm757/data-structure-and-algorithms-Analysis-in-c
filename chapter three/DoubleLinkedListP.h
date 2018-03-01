#ifndef _Double_List_H

typedef int ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode DList;
typedef PtrToNode Position;

struct Node
{
    ElementType Element;
    Position Next;
    Position Prev;
};

DList Create( DList L );
DList MakeEmpty( DList L );
int IsEmpty( DList L );
int IsLast( Position P, DList L );
int IsFirst( Position P, DList L );
Position Find( ElementType X, DList L );
DList Delete( ElementType X, DList L );
DList Insert( ElementType X, Position P, DList L );
Position First( DList L );
Position Last( DList L );
Position Advance( Position P );
ElementType Retrieve( Position P );
void Print( DList L );

#endif
