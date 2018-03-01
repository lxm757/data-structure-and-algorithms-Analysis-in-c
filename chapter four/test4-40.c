#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Defination  */
typedef int ElementType;
typedef struct TreeNode
{
    ElementType Element;
    struct TreeNode *Brother;
    struct TreeNode *Child;
} **Tree, *Position;

/* Test new structure of tree  */
Tree Create( void )
{
    Tree T;
    T = ( Tree )malloc( 
            sizeof( Position ) );
    if( T == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    *T = NULL;
    return T;
}

/* Return pointer point to tree node  */
Position GetTreeNode( ElementType X )
{
    Position P;
    P = ( Position )malloc( 
            sizeof( struct TreeNode ) );
    if( P == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    P->Element = X;
    P->Brother = P->Child = NULL;
    return P;
}

/* Set srand  */
void SetSrand( void )
{
    srand( ( unsigned int )time( NULL ) );
}

/* Return numbers  */
int GetCount( void )
{
    static int Count; 
    return ++Count;
}

/* Draw random tree  */
static Position DrawRandomTree( Position P )
{
    int Brother;
    Position Tmp;

    if( P != NULL )
    {
        /* Child is not empty  */
        return P;
    }
    
    Brother = rand( ) % 3;
    if( Brother )
    {
        while( Brother-- )
        {
            Tmp = GetTreeNode( GetCount( ) );
            Tmp->Brother = P;
            P = Tmp;
            P->Child = DrawRandomTree( P->Child );
        }
    }
    return P;
}

/* Draw a tree  */
Tree DrawTree( Tree T )
{
    Position P;

    if( T != NULL && *T != NULL )
    {
        return T;
    }
    else if( T == NULL )
    {
        T = Create( );
    }
    /* Else *T is NULL  */
    /* Insert root  */
    P = GetTreeNode( GetCount( ) );
    *T = P;
    /* Insert child  */    
    ( *T )->Child = DrawRandomTree( ( *T )->Child );

    return T;
}

/* Print tree  */
void PrintTree( Tree T )
{
    Position P;
    if( T != NULL && *T != NULL )
    {
        P = *T;
        while( P != NULL )
        {
            /* Print child  */
            PrintTree( &( P->Child ) );
            /* Print node element  */
            printf( "%d\n", P->Element );
            P = P->Brother;
        }
    }
}

/* Draw a tree  */
void Draw( Tree T ) { Position P;
    P = GetTreeNode( 1 );
    /* Insert root  */
    *T = P;
    /* Insert subtree  */
    P->Child = GetTreeNode( 2 );
    P->Child->Brother = GetTreeNode( 3 );

    P = P->Child;
    P->Child = GetTreeNode( 4 );
    P->Brother->Child = GetTreeNode( 5 );
}

/* Test  */
int main( void )
{
    SetSrand( );
    Tree T;
    T = Create( );
    T = DrawTree( T );
    //Draw( T );
    PrintTree( T );
    return 0;
}
