#ifndef _AVLTree_H

typedef int ElementType;
struct AvlNode;
typedef struct AvlNode *Position;
typedef Position *AvlTree;

AvlTree Create( void );
void MakeEmpty( AvlTree );
Position Find( ElementType, AvlTree );
Position FindMin( AvlTree );
Position FindMax( AvlTree );
void Insert( ElementType, AvlTree );
void Delete( ElementType, AvlTree );
ElementType Retrieve( Position );

#endif
