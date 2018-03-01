#ifndef _Double_Circle_List_H

typedef int ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode *DCList;
typedef PtrToNode Position;

struct Node
{
    ElementType Element;
    Position Next;
    Position Prev;
};

DCList Create( DCList );
void MakeEmpty( DCList );
int IsEmpty( DCList );
int IsLast( Position, DCList );
int IsFirst( Position, DCList );
Position Find( ElementType, DCList );
void Delete( ElementType, DCList );
void DeletePosition( Position, DCList );
void DeleteList( DCList L );
void Insert( ElementType, Position, DCList );
Position First( DCList );
Position Last( DCList );
Position Advance( Position );
Position Previous( Position );
ElementType Retrieve( Position );
void Print( DCList );
void PrintInReverse( DCList );

#endif
