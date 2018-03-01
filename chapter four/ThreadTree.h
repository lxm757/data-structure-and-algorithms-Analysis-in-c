#ifndef _ThreadTree_H

typedef int ElementType;
struct ThreadTreeNode;
typedef struct ThreadTreeNode *Position;
typedef Position *ThreadTree;

ThreadTree Create( );
void MakeEmpty( ThreadTree );
void Insert( ElementType, ThreadTree );
void Delete( ElementType, ThreadTree );
void PrintTree( ThreadTree );
ElementType Retrieve( Position );

#endif
