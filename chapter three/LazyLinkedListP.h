#ifndef _Lazy_List_H

typedef int ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node
{
    ElementType Element;
    char IsDeleted;
    Position Next;
};

List Create( void );
List MakeEmpty( List );
int IsEmpty( List );
int IsLast( Position, List );
Position Find( ElementType, List );
void Delete( ElementType, List );
Position FindPrevious( ElementType, List );
void Insert( ElementType, Position, List );
void DeleteList( List );
Position Header( List );
Position First( List );
Position Last( List );
Position Next( Position, List );
Position Advance( Position );
ElementType Retrieve( Position );
void Print( List );

#endif
