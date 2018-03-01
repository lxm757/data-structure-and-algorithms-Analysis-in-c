#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct TreeNode
{
    ElementType Element;
    struct TreeNode *Left;
    struct TreeNode *Right;
} *Tree;

/* Allocate memory for tree node  */
Tree AllocateMemory( Tree T, ElementType X )
{
    if( T == NULL )
    {
        T = ( Tree )malloc( 
                sizeof( struct TreeNode ) );
        if( T == NULL )
        {
            printf( "Out of space !!!" );
            exit( 1 );
        }
        T->Element = X;
        T->Left = T->Right = NULL;
    }
    return T;
}

int IsIsomorphic( Tree T1, Tree T2 )
{
    if( T1 == NULL || T2 == NULL )
    {
        /* Both node is empty, they are the same  */
        /* otherwise they are not the same  */
        return T1 == NULL && T2 == NULL;
    }
    else /* Two node elements are equals  */
    {
        if( T1->Element == T2->Element )
        {
            return ( IsIsomorphic( T1->Left, T2->Right ) 
                    && IsIsomorphic( T1->Right, T2->Left ) ) ||
                    ( IsIsomorphic( T1->Left, T2->Left ) 
                      && IsIsomorphic( T1->Right, T2->Right ) );
        }
        else
        {
            return 0;
        }
    }
    
}

/*   */
int main( void )
{
    Tree T1, T2;
    T1 = T2 = NULL;

    /* Allocate memory for new tree T1  */
    T1 = AllocateMemory( T1, 1 );
    /* Insert left and right subtree  */
    T1->Left = AllocateMemory( T1->Left, 2 );
    T1->Right = AllocateMemory( T1->Right, 3 );
    
    /* Allocate memory for new tree T1  */
    T2 = AllocateMemory( T2, 1 );
    /* Insert left and right subtree  */
    T2->Left = AllocateMemory( T2->Left, 3 );
    T2->Right = AllocateMemory( T2->Right, 2 );

#if 1 
    printf( "Tree1: \n" );
    printf( "    1\n" );
    printf( "   / \\\n" );
    printf( "  2   3\n" );

    printf( "Tree2: \n" );
    printf( "    1\n" );
    printf( "   / \\\n" );
    printf( "  3   2\n" );
#endif

    printf( "They %s isomorphic\n",
            IsIsomorphic( T1, T2 ) ? "are" : "are not" );

    return 0;
}

