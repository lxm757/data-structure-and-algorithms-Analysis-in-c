#include "SplayTree.h" 
#include <stdio.h> 
#include <stdlib.h> 

/* Splay tree node  */
struct TreeNode
{
    ElementType Element;
    PtrToNode Left;
    PtrToNode Right;
}; 

/* Create splay tree  */
SplayTree Create( void )
{
    SplayTree T;
    T = ( SplayTree )malloc(
            sizeof( PtrToNode ) );
    if( T == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    *T = NULL;
    return T;
}

/* Make splay tree empty  */
void MakeEmpty( SplayTree T )
{
    if( T != NULL && *T != NULL )
    {
        MakeEmpty( &( *T )->Left );
        MakeEmpty( &( *T )->Right );
        free( *T );
        *T = NULL;
    }
}

/* Insert element into splay tree  */
/* Assume T is a legal tree  */
void Insert( ElementType X, SplayTree T )
{
    if( *T == NULL )
    {
        *T = ( PtrToNode )malloc(
                sizeof( struct TreeNode ) );
        if( *T == NULL )
        {
            printf( "Out of space !!!" );
            exit( 1 );
        }
        ( *T )->Element = X;
        ( *T )->Left = ( *T )->Right = NULL;
    }
    else if( X < ( *T )->Element )
    {
        Insert( X, &( *T )->Left );
    }
    else if( X > ( *T )->Element )
    {
        Insert( X, &( *T )->Right );
    }
    /* Else X is in the tree already; we'll do nothing  */
}

/* Delete position of element X  */
void Delete( ElementType X, SplayTree T )
{
    Position Tmp;
    if( T != NULL && *T != NULL )
    {
        if( X < ( *T )->Element )
        {
            Delete( X, &( *T )->Left );
        }
        else if( X > ( *T )->Element )
        {
            Delete( X, &( *T )->Right );
        }
        else /* Equal to  */
        {
            if( ( *T )->Left != NULL && ( *T )->Right != NULL )
            {
                /* handles two childrens  */
                Tmp = FindMin( &( *T )->Right );
                ( *T )->Element = Tmp->Element;
                Delete( Tmp->Element, &( *T )->Right );
            }
            else if( ( *T )->Left != NULL )
            {
                /* Handles one left children  */
                Tmp = *T;
                *T = ( *T )->Left;
                free( Tmp );
            }
            else 
            {
                /* Handles one right children  */
                /* Also handles 0 children  */
                Tmp = *T;
                *T = ( *T )->Right;
                free( Tmp );
            }
        }
    }
}

/* Find position of minimum element  */
Position FindMin( SplayTree T )
{
    Position P;
    P = NULL;
    if( T != NULL && *T != NULL )
    {
        P = *T;
        while( P->Left != NULL )
        {
            P = P->Left;
        }
    }
    return P;
}

/* Find position of maximum element  */
Position FindMax( SplayTree T )
{
    Position P;
    P = NULL;
    if( T != NULL && *T != NULL )
    {
        P = *T;
        while( P->Right != NULL )
        {
            P = P->Right;
        }
    }
    return P;
}

/* Retrieve element of position P  */
/* Assume P is a legal position  */
ElementType Retrieve( Position P )
{
    return P->Element;
}

/* Inorder treversal  */
/* Assume T is a legal tree  */
void Print( SplayTree T )
{
    /*  
    if( T == NULL )
    {
        printf( "Illegal tree" );
        exit( 1 );
    }
    */

    if( *T != NULL )
    {
        Print( &( *T )->Left );
        printf( "%d\n", Retrieve( *T ) );
        Print( &( *T )->Right );
    }
}

/* Single rotate with left  */
static Position SingleRotateWithLeft( Position P )
{
    Position TmpCell;
    TmpCell = P->Left;
    P->Left = TmpCell->Right;
    TmpCell->Right = P;
    return TmpCell;
}

/* Single rotate with right  */
static Position SingleRotateWithRight( Position P )
{
    Position TmpCell;
    TmpCell = P->Right;
    P->Right = TmpCell->Left;
    TmpCell->Left = P;
    return TmpCell;
}

/* Double rotate wtih left - right */
static Position DoubleRotateWithLeftRight( Position P )
{
    P->Left = SingleRotateWithRight( P->Left );
    return SingleRotateWithLeft( P );
}

/* Double rotate with right - left */
static Position DoubleRotateWithRightLeft( Position P )
{
    P->Right = SingleRotateWithLeft( P->Right );
    return SingleRotateWithRight( P );
}

/* Double rotate with left - left  */
static Position DoubleRotateWithLeftLeft( Position P )
{
    P = SingleRotateWithLeft( P );
    return SingleRotateWithLeft( P );
}

/* Double rotate with right - right  */
static Position DoubleRotateWithRightRight( Position P )
{
    P = SingleRotateWithRight( P );
    return SingleRotateWithRight( P );
}

/* Find position of element X  */
/* Recursive implementation ????  */
static Position FindX( ElementType X, SplayTree T, Position Root)
{
    Position P;
    P = *T;
    if( P == NULL )
    {
        return NULL;
    }
    else if( X < ( *T )->Element )
    {
        //printf( " -- Left Find %d\n", ( *T )->Element );
        P = FindX( X, &( P->Left ), Root );
        if( P != NULL )
        {
            if( X < ( *T )->Left->Element )
            {
                /* Left - Left condition  */
                /* Single rotate from *T to left child  */
                //printf( "Left - Left Double Rotate %d\n", ( *T )->Element );
                *T = DoubleRotateWithLeftLeft( *T );
            }
            else if( X > ( *T )->Left->Element )
            {
                /* Left - Right condition  */
                /* Double rotate *T  */
                //printf( "Left - Right Double Rotate %d ", ( *T )->Element ); 
                *T = DoubleRotateWithLeftRight( *T );
                //printf( "End\n" );
            }
            else 
            {
                /* X is equal to element of left child  */
                if( *T == Root )
                {
                    /* Left condition  */
                    /* Single left rotation  */
                    //printf( "Left Single Rotate %d\n ", ( *T )->Element );
                    *T = SingleRotateWithLeft( *T );
                    //printf( "End\n" );
                }
            }
        }
    }
    else if( X > ( *T )->Element )
    {
        //printf( " -- Right Find %d\n", ( *T )->Element );
        P = FindX( X, &( P->Right ), Root );
        if( P != NULL )
        {
            if( X < ( *T )->Right->Element )
            {
                /* Right - Left condition  */
                //printf( "Right - Left Double Rotate %d\n ", ( *T )->Element );
                *T = DoubleRotateWithRightLeft( *T );
                //printf( "End\n" );
            }
            else if( X > ( *T )->Right->Element )
            {
                /* Right - Right condition  */
                //printf( "Right - Right Double Rotate %d\n ", ( *T )->Element );
                *T = DoubleRotateWithRightRight( *T );
                //printf( "End\n" );
            }
            else 
            {
                /* X is equal to element of right child  */
                if( *T == Root )
                {
                    /* Right condition  */
                    //printf( "Right Single Rotate %d\n ", ( *T )->Element );
                    *T = SingleRotateWithRight( *T );
                    //printf( "End\n" );
                }
            }
        }
    }

    return P;
}

/* This is a test of Find  */
/* Assume T is a legal tree  */
Position Find( ElementType X, SplayTree T )
{
    return FindX( X, T, *T );
}

/* Last Node is the address containing last value that
 * was assigned to a node  */
static Position GenTree( int Height, int *LastNode )
{
    Position T;
    
    T = NULL;
    if( Height >= 0 )
    {
        T = ( Position )malloc( 
                sizeof( struct TreeNode ) );
        if( T != NULL )
        {
            /* Use inorder traversal to confirm  
             * tree is a binary tree  */
            /* Use the same height to 
             * confirm tree is a full tree  */
            T->Left = GenTree( Height - 1, LastNode );
            T->Element = ++*LastNode;
            T->Right = GenTree( Height - 1, LastNode );
        }
        else
        {
            printf( "Out of space !!!" );
        }
    }
    return T;
}

/* General function  */
SplayTree PerfectTree( int H, SplayTree T )
{
    int LastNodeAssigned = 0;
    if( T == NULL )
    {
        T = Create( );
    }    
    
    if( *T == NULL )
    {
        *T = GenTree( H, &LastNodeAssigned ); 
    }

    return T;
}

///* Test  */
//int main( void )
//{
//    SplayTree T;
//    T = Create( );
//    /* Binary tree test */
//    printf( "Insert\n" );
//    Insert( 7, T );
//    Insert( 6, T );
//    Insert( 5, T );
//    Insert( 4, T );
//    Insert( 3, T );
//    Insert( 2, T );
//    Insert( 1, T );
//
//    printf( "Print\n" );
//    Print( T );
//
//    /* Binary tree OK  */
//
//    printf( "Find\n" );
//    Position Tmp;
//    Tmp = Find( 1, T );
//    
//    if( Tmp != NULL )
//    {
//        printf( "%d\n", Tmp->Element );
//    }
//    else
//    {
//        printf( "NULL\n" );
//    }
//    /* Left - Left OK  */
//    /* Right - Right OK  */
//    /* Left - Right  OK */
//    /* Right - Left   */
//
//    MakeEmpty( T );
//    Print( T );
//    printf( "\n" );
//
//    printf( "Generate a perfect tree:\n" );
//    T = PerfectTree( 2, T );    
//    Print( T );
//
//    return 0;
//}
//
//
