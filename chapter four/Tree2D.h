#ifndef _Tree2D_H

typedef char *Key;
typedef Key ElementType;
struct TreeNode;
typedef struct TreeNode **Tree2D;
typedef struct TreeNode *Position;

Tree2D Create( Tree2D );
void MakeEmpty( Tree2D );
Tree2D Dispose( Tree2D );
void Insert( ElementType, Tree2D );
//void PrintRange( Key, ... );
ElementType Retrieve( Position );

#endif
