#include "ThreadTree.h"
#include <stdlib.h>
#include <stdio.h>

/* Tree node  */
struct ThreadTreeNode
{
    ElementType Element;
    Position Left;
    Position Right;
    int IsLeftThread;
    int IsRightThread;
};

/* Create and return new thread tree  */
ThreadTree Create( ThreadTree T )
{
    if( T != NULL )
    {
        printf( "Illegal parameter" );
    }
    else 
    {
        T = ( ThreadTree )malloc( 
                sizeof( struct ThreadTreeNode ) );
        if( T == NULL )
        {
            printf( "Out of space !!!" );
            exit( 1 );
        }
        *T = NULL;
    }
    return T;
}

/* Make empty  */
void MakeEmpty( ThreadTree T )
{
    if( T != NULL && *T != NULL )
    {
        MakeEmpty( &( *T )->Left );
        MakeEmpty( &( *T )->Right );
        free( *T );
        *T = NULL;
    }

}

/* Find position of minimum element  */
Position FindMin( ThreadTree T )
{
    Position Tmp;
    Tmp = NULL;
    if( T != NULL && *T != NULL )
    {
        Tmp = *T;
        while( !Tmp->IsLeftThread )
        {
            Tmp = Tmp->Left;
        }
    }
    return Tmp;
}

/* Find position of maximum element  */
Position FindMax( ThreadTree T )
{
    Position Tmp;
    Tmp = NULL;
    if( T != NULL && *T != NULL )
    {
        Tmp = *T;
        while( !Tmp->IsRightThread )
        {
            Tmp = Tmp->Right;
        }
    }
    return Tmp;
}

/* Insert element to thread tree  */
/* Assume thread tree is legal  */
void Insert( ElementType X, ThreadTree T )
{
    Position Tmp;

    if( *T == NULL )
    {
        /* Create a non-node tree  */
        *T = ( Position )malloc( 
                sizeof( struct ThreadTreeNode ) );
        if( *T == NULL )
        {
            printf( "Out of space !!!" );
            exit( 1 );
        }
        ( *T )->Element = X;
        /* Set left and right pointer are thread  */
        ( *T )->IsLeftThread = 1;
        ( *T )->IsRightThread = 1;
        /* Thread may also be null  */
        ( *T )->Left = ( *T )->Right = NULL;
    }
    else if( X < ( *T )->Element )
    {
        printf( " -- %d is samller then %d\n", X, ( *T )->Element );
        if( ( *T )->IsLeftThread )
        {
            /* If left pointer is thread before insert,
             * set left pointer point to empty, new node
             * should be inserted in left pointer */
            ( *T )->Left = NULL;
        }
        Insert( X, &( *T )->Left );
        if( ( *T )->IsLeftThread )
        {
            /* If left pointer is thread before  */
            /* Inserted a new node in left subtree  */
            /* Left pointer convert to child */
            ( *T )->IsLeftThread = 0;
            /* Convert left child right pointer point to
             * inorder successor  */
            ( *T )->Left->Right =  *T;
        }
        else 
        {
            /* If left pointer is child before  */
            /* Inserted a new node in left subtree  */
            if( ( Tmp = FindMax( &( *T )->Left ) )->Element == X )
            {
                /* Convert new node's right pointer to 
                 * point to inorder successor  */
                Tmp->Right = *T;
            }
            /* Can also use:
             * FindMax( &( *T )->Left )->Right = *T;  */
        }
    }
    else if( X > ( *T )->Element )
    {
        printf( " -- %d is lager then %d\n", X, ( *T )->Element );
        if( ( *T )->IsRightThread )
        {
            /* If right pointer is thread before insert,
             * set right pointer point to emtpy, new node
             * should be inserted in right pointer   */
            ( *T )->Right = NULL;
        }
        Insert( X, &( *T )->Right );
        if( ( *T )->IsRightThread )
        {
            /* If right pointer is thread before
             * inserted a new node in right subtree
             * convert right pointer to child  */
            ( *T )->IsRightThread = 0;
            /* Convert right child's left pointer to
             * point to inorder predecessor  */
            ( *T )->Right->Left = *T;
        }
        else
        {
            /* If right pointer is child before
             * inserted a new node in right subtree  */
            if( ( Tmp = FindMin( &( *T )->Right ) )->Element == X )
            {
                /* Convert new node's left pointer to
                 * point to inorder predecessor  */
                Tmp->Left = *T;
            }
        }
    }
}

/* Delete position of element X  */
static Position DeleteX( ElementType X, Position P )
{
    Position TmpCell;
    if( X < P->Element && !P->IsLeftThread )
    {
        /* Keep left child inorder predecessor  */
        TmpCell = P->Left->Left;
        P->Left = DeleteX( X, P->Left );
        if( P->Left == NULL )
        {
            /* Left child been deleted,
             * refresh left thread  */
            P->IsLeftThread = 1;
            P->Left = TmpCell;
        }
    }
    else if( X > P->Element && !P->IsRightThread )
    {
        /* Keep right child inorder successor  */
        TmpCell = P->Right->Right;
        P->Right = DeleteX( X, P->Right );
        if( P->Right == NULL )
        {
            /* Right child been deleted,
             * refresh right thread  */
            P->IsRightThread = 1;
            P->Right = TmpCell;
        }
    }
    else /* Element found, delete it  */
    {
        /* two children  */
        if( !P->IsLeftThread && !P->IsRightThread )
        {
            TmpCell = FindMin( &P->Right );
            P->Element = TmpCell->Element;
            /* Keep right child inorder successor  */
            TmpCell = P->Right->Right;
            P->Right = DeleteX( P->Element, P->Right );
            if( P->Right == NULL )
            {
                /* Right child been deleted,
                 * refresh right thread  */
                P->IsRightThread = 1;
                P->Right = TmpCell;
            }
        }
        else if( !P->IsLeftThread )
        {
            /* Left child is not empty and 
             * right child is empty  */
            TmpCell = P;
            P = P->Left;
            /* Refresh thread  */
            ( FindMax( &P ) )->Right = TmpCell->Right;
            free( TmpCell );
        }
        else if( !P->IsRightThread )
        {
            /* Left child is empty and 
             * right child is not empty  */
            TmpCell = P;
            P = P->Right;
            /* Refresh thread  */
            ( FindMin( &P ) )->Left = TmpCell->Left;
            free( TmpCell );
        }
        else 
        {
            /* Left and right child are empty  */
            free( P );
            P = NULL;
        }
    }
    return P;
}

/* Delete element  */
void Delete( ElementType X, ThreadTree T )
{
    if( T != NULL && *T != NULL )
    {
        *T = DeleteX( X, *T );
    }
    /* Illegal parameter  */
}

/* Print tree inorder  */
/* Parameter is not empty  */
static void PrintOnlyLeft( Position P )
{
    Position Tmp = FindMin( &P );
    while( Tmp != P )
    {
        printf( "%d\n", Tmp->Element );
        Tmp = Tmp->Right;
    } 
    printf( "%d\n", P->Element );
}

static void PrintOnlyRight( Position P )
{
    Position Tmp = FindMax( &P );
    while( Tmp != P )
    {
        printf( "%d\n", Tmp->Element );
        Tmp = Tmp->Left;
    }
    printf( "%d\n", P->Element );
}

/* Print tree inorder */
/* The tree is a special tree, 
 * which only has left subtree or right subtree */
void PrintTree( ThreadTree T )
{
    if( T != NULL && *T != NULL )
    {
        if( ( *T )->Left == NULL && 
                ( *T )->Right == NULL )
        {
            printf( "Only has one root: \n" );
            PrintOnlyLeft( *T );
        }
        if( ( *T )->Left != NULL )
        {
            printf( "Lower: from left position of\n"
                    "minimum element to root: \n" );
            PrintOnlyLeft( *T );
        }
        if( ( *T )->Right != NULL )
        {
            printf( "Upper: from right position of\n"
                    "maximum element to root: \n" );
            PrintOnlyRight( *T );
        }
    }
    else
    {
        printf( "Empty tree" );
    }
}

#if 1
/* Test  */
int main( void )
{
    ThreadTree T = NULL;
    T = Create( T );
#if 0
    Insert( 2, T );
    //printf( "can do this?\n" );
    Insert( 1, T );
    //printf( "can do this?\n" );
    Insert( 3, T );
    //printf( "can do this?\n" );
#endif

    Insert( 3, T );
    Insert( 1, T );
    Insert( 2, T );
    Insert( 0, T );
    Insert( 4, T );
    Insert( 5, T );

    PrintTree( T );
    putchar( '\n' );

    Delete( 3, T );
    PrintTree( T );
    putchar( '\n' );

    Delete( 1, T );
    PrintTree( T );
    putchar( '\n' );

    Delete( 0, T );
    PrintTree( T );
    putchar( '\n' );

    Delete( 2, T );
    PrintTree( T );
    putchar( '\n' );

    Delete( 4, T );
    PrintTree( T );
    putchar( '\n' );

    Delete( 5, T );
    PrintTree( T );
    putchar( '\n' );

    return 0;
}

#endif

