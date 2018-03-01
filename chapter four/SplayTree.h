#ifndef _SplayTree_H

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *PtrToNode;
typedef PtrToNode *SplayTree;
typedef PtrToNode Position;

SplayTree Create( void );
void MakeEmpty( SplayTree );
Position Find( ElementType, SplayTree );
Position FindMin( SplayTree );
Position FindMax( SplayTree );
void Insert( ElementType, SplayTree );
void Delete( ElementType, SplayTree );
ElementType Retrieve( Position );

#endif
