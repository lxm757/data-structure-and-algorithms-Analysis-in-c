#include "Btree.h"
#include <stdio.h>
#include <stdlib.h>

/* 2, 3, 4, ...  */
#define M 4 

/* Define struct of tree node  */
/* Do not use stack, use heap  */
struct TreeNode
{
    /* Better to use linked list 
     * to improve performance  */
    ElementType Element[ M + 1 ];
    int ElementCount;
    int Height;
    Position Childs[ M + 1 ];
#if 0
    ElementType *Element;
    int ElementCount;
    Position *Childs;
#endif
};

/* Initialize tree  */
BTree InitBTree( BTree T )
{
    if( T == NULL )
    {
        T = ( BTree )malloc(
                sizeof( Position ) );
        if( T == NULL )
        {
            printf( "Out of space !!!" );
            printf( " Can't alloc memory\n" );
        }
        else
        {
            *T = NULL;
        }
    }
    return T;
}

/* Create and return a new node  */
/* if Count is 0, return a empty node,
 * else if Count > 0, return a node with Count elements  */
/* All returned node has height with 0  */
static Position NewNode( int Count, ElementType Element[ ] )
{
    Position P;
    int i;

    P = ( Position )malloc(
            sizeof( struct TreeNode ) );
    if( P == NULL )
    {
        printf( "Out of space !!!" );
        printf( " Can't alloc memory\n" );
    }
    else
    {
        for( i = 0; i < Count; i++ )
        {
            P->Element[ i ] = Element[ i ];
        }
        /* Set size of elements  */
        P->ElementCount = Count;
        /* set height of node  */
        P->Height = 0;
        for( i = 0; i < M + 1; i++ )
        {
            P->Childs[ i ] = NULL;
        }
    }
    return P;
}

/* Binary search  */
/* Return -1 if found, >0 if not found  */
static int BinarySearch( ElementType X, Position P )
{
    int i, j, mid;
    /*Set i to left  */
    i = 0;
    /* Set j to right  */
    j = P->ElementCount - 1;
    /* Get middle  */
    while( i <= j )
    {
        mid = ( j - i )/2 + i;
        /* Compare two keys  */
        if( X < P->Element[ mid ] )
        {
            j = mid - 1;
        }
        else if( X > P->Element[ mid ] )
        {
            i = mid + 1;
        }
        else 
        {
            /* Found element, do nothing  */
            return -1;
        }
    }
    return i;
}

/* Insert X in P at position Pos  */
/* Assume all legal parameter used  */
static void InsertElementPos( ElementType X, int Pos, Position P )
{
    int i;
    if( P != NULL && Pos >= 0 )
    {

        /* This used array implementation
         * Another way used linked list implementation  */

        /* Move element to behind position  */
        for( i = P->ElementCount; i > Pos; i-- )
        {
            /* Error  */
            P->Element[ i ] = P->Element[ i - 1 ];
        }
        /* Insert in right position  */
        P->Element[ Pos ] = X;
        /* Refresh element count  */
        ++P->ElementCount;
        /* No need to refresh height  */

    }
    else
    {
        printf( "Illegal parameter" );
    }
}

/* Is leaf  */
static int IsLeaf( Position P )
{
    return P->Childs[ 0 ] == NULL;
}

/* Divide leaf node into two node, another way */
static Position DivideLeafs( Position P )
{
    int LeftSize, RightSize, i;
    ElementType Element[ M ];

    i = P->ElementCount;
    LeftSize = ( i % 2 ) ? ( i / 2 + 1 ) : ( i / 2 );
    RightSize = i / 2;

    /* Set left node element  */
    for( i = 0; i < LeftSize; i++ )
    {
        Element[ i ] = P->Element[ i ];
    }
    P->Childs[ 0 ] = NewNode( LeftSize, Element );

    /* Set right node element  */
    for( i = 0; i < RightSize; i++ )
    {
        Element[ i ] = P->Element[ i + LeftSize ];
    }
    P->Childs[ 1 ] = NewNode( RightSize, Element );

    /* Set parent node  */
    P->Element[ 0 ] = P->Element[ LeftSize ];
    P->ElementCount = 1;
    P->Height = 1;
    
    /* Is all ok  */
    if( P->Childs[ 0 ] == NULL || P->Childs[ 1 ] == NULL )
    {
        P->Childs[ 0 ] = P->Childs[ 1 ] = NULL;
    }
    return P;
}

/* Return number of childs  */
static int GetChildCount( Position P )
{
    /* Number of childs  */
    int Count;
    /* The number should not more than M  */
    for( Count = 0;  ( Count <= M ) && P->Childs[ Count ]; Count++ );
    return Count;
}

/* Insert child in p at pos  */
static void InsertChildPos( Position Child, int Pos, Position P )
{
    int i;

    for( i = GetChildCount( P ); i > Pos; i-- )
    {
        P->Childs[ i ] = P->Childs[ i - 1 ];
    }

    P->Childs[ Pos ] = Child;
    
    /* No need to refresh height  */
}

/* Marge parent P and its child  */
static void MergeChild( Position P, int Pos )
{
    Position Child;
    /* i for parent, j for child  */
    int i, j;

    Child = P->Childs[ Pos ];

    /* Merge element at pos  */
    for( i = Pos, j = 0; 
            j < Child->ElementCount; i++, j++ )
    {
        /* Insert at pos  */
        InsertElementPos( Child->Element[ j ], i, P );
    }

    /* Merge child at pos  */
    for( i = Pos, j = 0; j < GetChildCount( Child ) - 1; i++, j++ )
    {
        InsertChildPos( Child->Childs[ j ], i, P );
    }
    P->Childs[ i ] = Child->Childs[ j ];
    free( Child );

    /* Refresh height  */
    /* No need to Refresh  */
    
}

/* Find minimum  */
static Position FindMin( Position P )
{
    if( P != NULL )
    {
        while( P->Childs[ 0 ] != NULL )
        {
            P = P->Childs[ 0 ];
        }
    }
    return P;
}

/* Divide non leaf node  */
static void DivideNonLeaf( Position P )
{
    Position LeftNode, RightNode;
    /* The number of left and right childs  */
    int LeftChildSize, RightChildSize;
    int i;

    LeftNode = NewNode( 0, NULL );
    RightNode = NewNode( 0, NULL );
    LeftChildSize = GetChildCount( P ) % 2 ? 
        GetChildCount( P ) / 2 + 1 : GetChildCount( P ) / 2;
    RightChildSize = GetChildCount( P ) / 2;

    if( LeftNode != NULL && RightNode != NULL )
    {
        /* Deal with Left new node  */
        /* Insert child  */
        InsertChildPos( P->Childs[ 0 ], 0, LeftNode );
        for( i = 1; i < LeftChildSize; i++ )
        {
            InsertChildPos( P->Childs[ i ], i, LeftNode );

            InsertElementPos( FindMin( P->Childs[ i ] )->Element[ 0 ],
                    i - 1, LeftNode );

        }
        /* Refresh height  */
        LeftNode->Height = LeftNode->Childs[ 0 ]->Height + 1;

        /* Deal with right new node  */
        /* Insert cild  */
        InsertChildPos( P->Childs[ LeftChildSize ], 0, RightNode );
        for( i = 1; i < RightChildSize; i++ )
        {
            InsertChildPos( P->Childs[ i + LeftChildSize ], 
                    i, RightNode );
            InsertElementPos( 
                    FindMin( P->Childs[ i + LeftChildSize ] )->Element[ 0 ],
                    i - 1, RightNode );
        }
        /* Refresh height  */
        RightNode->Height = RightNode->Childs[ 0 ]->Height + 1;

        /* Deal with parent P  */
        /* Insert two childs  */
        P->Childs[ 0 ] = LeftNode;
        P->Childs[ 1 ] = RightNode;
        for( i = 2; i < M + 1; i++ )
        {
            P->Childs[ i ] = NULL;
        }
        /* Refresh element  */
        P->Element[ 0 ] = FindMin( P->Childs[ 1 ] )->Element[ 0 ];
        P->ElementCount = 1;
        /* Refresh height  */
        P->Height = P->Childs[ 0 ]->Height + 1;

    }
    
}

/* Insert element  */
static Position InsertX( ElementType X, Position P )
{
    /* Position or child number to insert */
    int Pos, Height;
    if( P == NULL )
    {
        /* Create new node  */
        //P = NewNode( X );
        P = NewNode( 1, &X );
    }
    else 
    {
        /* Insert element  */
        /* Find position or child number to insert  */
        Pos = BinarySearch( X, P );
        /* Pos > 0, found position or number  */
        if( Pos >= 0 )
        {
            if( !IsLeaf( P ) )
            {
                /* Keep child height before insert  */
                Height = P->Childs[ Pos ]->Height;
                /* Psoition is not a leaf node,
                 * find leaf node use child number  */
                P->Childs[ Pos ] = InsertX( X, P->Childs[ Pos ] );

                /* After inserted element in subtree  */
                if( P->Childs[ Pos ]->Height > Height )
                {
                    /* Subtree divided  */
                    /* Merge node  */
                    MergeChild( P, Pos );
                }
                /* After Merged  */
                if( GetChildCount( P ) > M )
                {
                    /* Divide non leaf node  */
                    DivideNonLeaf( P );
                }


            }
            else
            {
                /* In a leaf node  */
                /* insert element temporarily */
                InsertElementPos( X, Pos, P );

                /* Is node need to be divided  */
                if( P->ElementCount > M )
                {
                    /* Divide leaf  */
                    P = DivideLeafs( P );
                }
            }
        }
        else
        {
            /* Pos < 0, element already in position,
             * do nothing  */
        }

    } 
    return P;
}

/* Insert  */
void Insert( ElementType X, BTree T )
{
    if( T == NULL )
    {
        /* Illegal tree  */
        printf( "Illegal parameter\n" );
    }
    else
    {
        /* Make sure tree is leagl  */
        *T = InsertX( X, *T );
    }
}

/* Print elements from node  */
static void PrintElement( Position P )
{
    int i;
    /* Print depth  */
    /* Print elements  */
    for( i = 0; i < P->ElementCount; i++ )
    {
        printf( "%d ", P->Element[ i ] );
    } 
    printf( "\n" );
}

/* Print tree leaves */
void PrintTree( BTree T, int Count )
{
    int i;
    if( T != NULL && *T != NULL )
    {
        if( IsLeaf( *T ) )
        {
            printf( "%3d : leaf : ", Count );
            PrintElement( *T );
        }
        else
        {
            printf( "%3d : not leaf : ", Count );
            PrintElement( *T );
            /* Print childs  */
            for( i = 0; i < M + 1; i++ )
            {
                PrintTree( &( *T )->Childs[ i ], Count + 1 );
            }
        }
    }
    else
    {
        /* Tree is empty, do nothing  */
    }
}

/* Test  */
static void Test( void )
{
    BTree T = NULL;
    T = InitBTree( T );
    int i, Upper;
#if 0 
    Upper = 13;
    for( i = 1; i <= Upper; i++ )
    {
        printf( "Insert %d in tree\n", i );
        Insert( i, T );
    }
    #endif
    /* error at insert 5  */
#if 0 
    Upper = 4;
    for( i = 9; i >= Upper; i-- )
    {
        printf( "Insert %d in tree\n", i );
        Insert( i, T );
    }
    
#endif

#if 1

    printf( "Insert 7 in tree\n" );
    Insert( 7, T );
    printf( "Insert 3 in tree\n" );
    Insert( 3, T );
    printf( "Insert 13 in tree\n" );
    Insert( 13, T );
    printf( "Insert 5 in tree\n" );
    Insert( 5, T );
    printf( "Insert 9 in tree\n" );
    Insert( 9, T );
    printf( "Insert 8 in tree\n" );
    Insert( 8, T );
    printf( "Insert 15 in tree\n" );
    Insert( 15, T );
    printf( "Insert 1 in tree\n" );
    Insert( 1, T );
    printf( "Insert 2 in tree\n" );
    Insert( 2, T );
    
   
#endif
    PrintTree( T, 0 );

}

int main( void )
{
#if 1
    Test( );
#endif
}
