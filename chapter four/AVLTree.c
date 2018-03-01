#include "AVLTree.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX( left, right ) \
    ( left ) > ( right ) ? ( left ) : ( right )

/* Tree node  */
struct AvlNode
{
    int Height;
    ElementType Element;
    Position Left;
    Position Right;
};

/* Create a new avl tree  */
AvlTree Create( void )
{
    AvlTree T = ( AvlTree )malloc(
            sizeof( Position ) );
    if( T == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    *T = NULL;
    return T;
}

/* Make avl tree empty  */
void MakeEmpty( AvlTree T )
{
    if( T != NULL && *T != NULL )
    {
        MakeEmpty( &( *T )->Left );
        MakeEmpty( &( *T )->Right );
        free( *T );
        *T = NULL;
    }
}

/* Find position of element x  */
Position Find( ElementType X, AvlTree T )
{
    Position P;
    if( T != NULL && *T != NULL )
    {
        P = *T;
        while( P != NULL )
        {
            if( X < P->Element )
            {
                P = P->Left;
            }
            else if( X > P->Element )
            {
                P = P->Right;
            }
            else
            {
                return P;
            }
        }
    }
    return NULL;
}

/* Find position of minimum element  */
Position FindMin( AvlTree T )
{
    if( T != NULL && *T != NULL )
    {
        if( ( *T )->Left == NULL )
        {
            return *T;
        }
        else 
        {
            return FindMin( &( *T )->Left );
        }
    }
    return NULL;
}

/* Find position of maximum element  */
Position FindMax( AvlTree T )
{
    Position P;
    if( T != NULL && *T != NULL )
    {
        P = *T;
        while( P->Left != NULL )
        {
            P = P->Left;
        }
        return P;
    }
    return NULL;
}

/* Height  */
static int Height( Position P )
{
    if( P == NULL )
    {
        return -1;
    }
    else 
    {
        return P->Height;
    }
}

/* Single rotate whit left  */
static Position SingleRotateWithLeft( Position P )
{
    Position TmpCell;
    TmpCell = P->Left;
    P->Left = TmpCell->Right;
    TmpCell->Right = P;
    /* Refresh heitht  */
    P->Height = MAX( Height( P->Left ), 
            Height( P->Right ) ) + 1;
    TmpCell->Height = MAX( Height( TmpCell->Left ), 
            Height( TmpCell->Right ) ) + 1;
    return TmpCell;
}

/* Single rotate wiht right  */
static Position SingleRotateWithRight( Position P )
{
    Position TmpCell;
    TmpCell = P->Right;
    P->Right = TmpCell->Left;
    TmpCell->Left = P;
    /* Refresh height  */
    P->Height = MAX( Height( P->Left ),
            Height( P->Right ) ) + 1;
    TmpCell->Height = MAX( Height( TmpCell->Left ),
            Height( TmpCell->Right ) ) + 1;
    return TmpCell;
}

/* Double rotate with left  */
static Position DoubleRotateWithLeft( Position P )
{
    P->Left = SingleRotateWithRight( P->Left );
    return SingleRotateWithLeft( P );
}

/* Double rotate with left, improved  */
/* SingelRotateWithLeft unused in this implementation  */
static Position DoubleRotateWithLeftImproved( Position P )
{
    Position LeftP, LeftRightP;
    LeftP = P->Left;
    LeftRightP = LeftP->Right;
    /* Balanced tree  */
    LeftP->Right = LeftRightP->Left;
    LeftRightP->Left = LeftP;
    P->Left = LeftRightP->Right;
    LeftRightP->Right = P;
    /* Refresh height  */
    LeftP->Height = ( MAX( Height( LeftP->Left ), 
                Height( LeftP->Right ) ) ) + 1;
    P->Height = ( MAX( Height( P->Left ),
                Height( P->Right ) ) ) + 1;
    LeftRightP->Height = ( MAX( Height( P->Left ),
                Height( P->Right ) ) ) + 1;
    return LeftRightP;
}

/* Double rotate with right  */
static Position DoubleRotateWithRight( Position P )
{
    P->Right = SingleRotateWithLeft( P->Right );
    return SingleRotateWithRight( P );
}

/* Max height  */
static int MaxHeight( Position L, Position R )
{
    int LeftHeight, RightHeight;
    LeftHeight = Height( L );
    RightHeight = Height( R );
    return LeftHeight > RightHeight ?
        LeftHeight : RightHeight;
}

/* Insert an element  */
/* Assume T is a legal tree  */
void Insert( ElementType X, AvlTree T )
{
    if( *T == NULL )
    {
        /* Create and return a one-node tree  */
        *T = ( Position )malloc( 
                sizeof( struct AvlNode ) );
        if( T == NULL )
        {
            printf( "Out of apce !!!" );
            exit( 1 );
        }
        ( *T )->Height = 0;
        ( *T )->Element = X;
        ( *T )->Left = ( *T )->Right = NULL;
    }
    else if( X < ( *T )->Element ) 
    {
        Insert( X, &( *T )->Left );
        if( Height( ( *T )->Left ) - Height( ( *T )->Right ) >= 2 )
        {
            if( X < ( *T )->Left->Element )
            {
                /* Left - Left Rotation  */
                *T = SingleRotateWithLeft( *T );
            }
            else 
            {
                /* Left - Right Rotation  */
                *T = DoubleRotateWithLeft( *T );
            }
        }
    }
    else if( X > ( *T )->Element )
    {
        Insert( X, &( *T )->Right );
        if( Height( ( *T )->Right ) - Height( ( *T )->Left ) >= 2 )
        {
            if( X < ( *T )->Right->Element )
            {
                /* Right - Left Rotation  */
                *T = DoubleRotateWithRight( *T );
            }
            else /* X > ( *T )->Right->Element  */
            {
                *T = SingleRotateWithRight( *T );
            }
        }
    }
    /* Else X is in the tree already; we'll do nothing  */
    
    ( *T )->Height = MAX( Height( ( *T )->Left ), 
                Height( ( *T )->Right ) ) + 1;
}

/* Insert an element, recursive  */
/* Assume T is a legal tree  */
/* Use stack  */
void InsertNoRecursive( ElementType X, AvlTree T )
{
    /* Use array stack to keep cell from root to X  */
    /* Assume we don't cross through the border  */
    /* The max height of avl tree is 255  */
    Position Stack[ 256 ], P, Prev;
    int i, Bufp;

    for ( i = 0; i < 256; i++ )
    {
        Stack[ i ] = NULL;
    }

    P = *T;
    Bufp = 0;

    while( P != NULL )
    {
        if( X < P->Element )
        {
            Stack[ Bufp++ ] = P;
            P = P->Left;
        }
        else if( X > P->Element )
        {
            Stack[ Bufp++ ] = P;
            P = P->Right;
        }
        else
        {
            return;
        }
    }

    //printf( " - Found position to insert %d\n", X );

    P = ( Position )malloc(
            sizeof( struct AvlNode ) );
    if( P == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    P->Height = 0;
    P->Element = X;
    P->Left = P->Right = NULL;

    if( Bufp <= 0 )
    {
        *T = P;
        //printf( " - Insert %d in empty tree\n", P->Element );
        return;
    }
    else if( X < Stack[ --Bufp ]->Element )
    {
        Stack[ Bufp ]->Left = P;
    }
    else 
    {
        Stack[ Bufp ]->Right = P;
    }

    /* Haven't refresh height  */
    
    
    //printf( "middle\n" );

    while( Bufp >= 0 )
    {
        P = Stack[ Bufp-- ];
        //printf( " - Left: %d Right %d\n", Height( P->Left ), Height( P->Right ) );
        if( X < P->Element )
        {
            if( Height( P->Left ) - Height( P->Right ) >= 2 )
            {
                if( X < P->Left->Element )
                {
                    /* Left - Left Rotation  */
                    //printf( " -- Left - Left Rotation %d\n", P->Element );
                    P = SingleRotateWithLeft( P );
                } 
                else /* X > P->Left->Element  */
                {
                    /* Left - Right Rotation  */
                    //printf( " -- Left - Right Rotation %d\n", P->Element );
                    P = DoubleRotateWithLeft( P );
                }
            }
        }
        else /* X > P->Element  */
        {
            if( Height( P->Right ) - Height( P->Left ) >= 2 )
            {
                if( X < P->Right->Element )
                {
                    /* Right - Left Rotation  */
                    //printf( " -- Right - Left Rotation %d\n", P->Element );
                    P = DoubleRotateWithRight( P );
                }
                else /* X > P->Right->Element  */
                {
                    /* Right - Right Rotation  */
                    //printf( " -- Right - Right Rotation %d\n", P->Element );
                    P = SingleRotateWithRight( P );
                }
            }
        }

        /* Refresh p node height  */
        /* Attation: when we use macro definition, we should
         * use brackets to include it, otherwise the result
         * of macro definition may changed  */
        P->Height = ( MAX( Height( P->Left ),
                Height( P->Right ) ) ) + 1;
        //printf( " ---- update %d height: %d\n", P->Element, P->Height );

        /* Get prev node, use root if stack is empty  */
        if( Bufp >= 0 )
        {
            Prev = Stack[ Bufp ];
            /* Let subtree in right position  */
            if( X < Prev->Element )
            {
                Prev->Left = P;
            }
            else /* X > P->Element  */
            {
                Prev->Right = P;
            }
        }
        else 
        {
            *T = P;
        }
    }
    //printf( " - Root %d\n", P->Element );
}

/* Delete element X  */
/* Assume T is a legal tree  */
void Delete( ElementType X, AvlTree T )
{
    Position TmpCell;
    if( *T == NULL )
    {
        printf( "Element not found" );
    }
    else if( X < ( *T )->Element )
    {
        Delete( X, &( *T )->Left );
        /* Delete node in left subtree may cause unbalanced  */
        /* Height of left subtree may decrease  */
        /* Rotate with right  */
        printf( " -- %d Left: %d Right: %d\n", Retrieve( *T ), 
                Height( ( *T )->Left ), Height( ( *T )->Right ) );
        if( Height( ( *T )->Right ) - Height( ( *T )->Left ) >= 2 )
        {
            TmpCell = ( *T )->Right;
            if( Height( TmpCell->Right ) >= Height( TmpCell->Left ) )
            {
                /* Right - Right Rotation  */
                printf( " --- SingleRotateWithLeft %d\n", Retrieve( *T ) );
                *T = SingleRotateWithRight( *T );
            }
            else 
            {
                /* Right - Left Rotation  */
                printf( " --- DoubleRotateWithLeft %d\n", Retrieve( *T ) );
                *T = DoubleRotateWithRight( *T );
            }
        }
    }
    else if( X > ( *T )->Element )
    {
        Delete( X, &( *T )->Right );
        /* Delete node in right subtree may cause unbalanced  */
        /* Height of right subtree may decrease  */
        /* Rotate with left  */
        printf( " -- %d Left: %d Right: %d\n", Retrieve( *T ),
                Height( ( *T )->Left ), Height( ( *T )->Right ) );
        if( Height( ( *T )->Left ) - Height( ( *T )->Right ) >= 2 )
        {
            TmpCell = ( *T )->Left;
            if( Height( TmpCell->Left ) >= Height( TmpCell->Right ) )
            {
                /* Left - Left Rotation  */
                printf( " --- SingleRotateWithRight %d\n", Retrieve( *T ) );
                *T = SingleRotateWithLeft( *T );
            }
            else
            {
                /* Left - Right Rotation  */
                printf( " --- DoubleRotateWithRight %d\n", Retrieve( *T ) );
                *T = DoubleRotateWithLeft( *T );
            }
        }
    }
    else 
    {
        if( ( *T )->Left && ( *T )->Right )
        {
            TmpCell = FindMin( &( *T )->Right );
            //printf( "Find minimum at right tree %d\n", TmpCell->Element );
            ( *T )->Element = TmpCell->Element;
            Delete( TmpCell->Element, &( *T )->Right );
            /* Found node, exchange node element with minimum element
             * found in right subtree  */
            /* Then delete minimum element in right subtree  */
            /* Height of right subtree may decrease  */
            /* Rotate with left  */
            printf( " -- %d Left: %d Right: %d\n", Retrieve( *T ),
                    Height( ( *T )->Left ), Height( ( *T )->Right ) );
            if( Height( ( *T )->Left ) - Height( ( *T )->Right ) >= 2 )
            {
                TmpCell = ( *T )->Left;
                if( Height( TmpCell->Left ) >= Height( TmpCell->Right ) )
                {
                    /* Left - Left Rotation  */
                    printf( " --- SingleRotateWithLeft %d\n", Retrieve( *T ) );
                    *T = SingleRotateWithLeft( *T );
                }
                else 
                {
                    /* Left - Right Rotation  */
                    printf( " --- DoubleRotateWithLeft %d\n", Retrieve( *T ) );
                    *T = DoubleRotateWithLeft( *T );
                }
            }
        }
        else 
        {
            TmpCell = *T;
            if( TmpCell->Left != NULL )
            {
                *T = TmpCell->Left;
            }
            else /* Also handles 0 children  */
            {
                *T = TmpCell->Right;
            }
            free( TmpCell );
        }
    }

    /* Refresh node height  */
    if( *T != NULL )
    {
        ( *T )->Height = ( MAX( Height( ( *T )->Left ), 
                    Height( ( *T )->Right ) ) ) + 1;
    }
    printf( " -- Update height\n" );
}

/* Retrieve element  */
/* Assume P is a legal position  */
ElementType Retrieve( Position P )
{
    if( P != NULL )
    {
        return P->Element;
    }
    return 0; /* This 0 is used to avoid warning  */
}

/* Print avl tree  */
void PrintTree( AvlTree T )
{
    if( T != NULL && *T != NULL )
    {
        PrintTree( &( *T )->Left );
        printf( "%d\n", ( *T )->Element );
        PrintTree( &( *T )->Right );
    }
}

/* LastNode is the address containing last value that
 * was assigned to a node  */
static Position GenTree( int Height, int *LastNode )
{
    Position T;

    T = NULL;
    if( Height >= 0 )
    {
        T = ( Position )malloc( 
                sizeof( struct AvlNode ) );
        if( T != NULL )
        {
            /* Inorder traversal 
             * to conform tree is a binary tree  */
            /* Use height to conform tree is a avl tree, 
             * N( H ) = N ( H - 1 ) + N( H - 2 ) + 1  */
            T->Left = GenTree( Height - 1, LastNode );
            T->Element = ++*LastNode;
            T->Right = GenTree( Height - 2, LastNode );
        }
        else 
        {
            printf( "Out of space !!!" );
        }
    }
    return T;
}

/* General function  */
AvlTree MinAvlTree( int H, AvlTree T )
{
    int LastNodeAddress;

    LastNodeAddress = 0;
    if( T == NULL )
    {
        T = Create( );
    }

    if( *T == NULL )
    {
        *T = GenTree( H, &LastNodeAddress );
    }
    return T;
}


///* Test  */
//int main( void )
//{
//    AvlTree T;
//    T = Create( );
//
//    /* Insert into tree  */
//    printf( "Insert 33\n" );
//    InsertNoRecursive( 33, T );
//    printf( "\nInsert 77\n" );
//    InsertNoRecursive( 77, T );
//    printf( "\nInsert 55\n" );
//    InsertNoRecursive( 55, T );
//    printf( "\nInsert 11\n" );
//    InsertNoRecursive( 11, T );
//    printf( "\nInsert  1\n" );
//    InsertNoRecursive(  1, T );
//    printf( "\nInsert  3\n" );
//    InsertNoRecursive(  3, T );
//    printf( "Root: %d\n", Retrieve( *T ) );
//    /* This tree should be like this:  */
//    /*          11                     */
//    /*        /    \                   */
//    /*       1      77                 */
//    /*      / \    /  \                */
//    /*    null 3  33  55               */
//
//    printf( "\n" );
//    PrintTree( T );
//    printf( "\n" );
//
//    /* Delete from tree  */
//    printf( "Delete 11\n" );
//    Delete( 11, T );
//    printf( "Delete 33\n" );
//    Delete( 33, T );
//    printf( "Delete 55\n" );
//    Delete( 55, T );
//    /* The tree should be like this after deleted: */
//    /*          3                                  */
//    /*        /   \                                */
//    /*       1     77                              */
//
//
//    printf( "\n" );
//    PrintTree( T );
//
//    MakeEmpty( T );
//    PrintTree( T );
//    printf( "\n" );
//
//    printf( "Generate a random avl tree:\n" );
//    T = MinAvlTree( 3, T );
//    PrintTree( T );
//
//    return 0;
//}
