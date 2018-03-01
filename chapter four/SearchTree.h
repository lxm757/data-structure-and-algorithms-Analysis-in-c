#ifndef _SearchTree_H

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode **SearchTree;
typedef struct TreeNode *Position;

SearchTree Create( void );
SearchTree MakeRandomTree( int, SearchTree );
void MakeEmpty( SearchTree );
Position Find( ElementType, SearchTree );
Position FindMin( SearchTree );
Position FindMax( SearchTree );
int CountNodes( SearchTree );
int CountLeaves( SearchTree );
int CountFull( SearchTree );
int Depth( ElementType, SearchTree );
void Insert( ElementType, SearchTree );
void Delete( ElementType, SearchTree );
void PrintTree( SearchTree );
void PrintInLevelOrder( SearchTree );
void PrintRange( ElementType, ElementType, SearchTree );
void DrawTree( SearchTree );
ElementType Retrieve( Position );


#endif
