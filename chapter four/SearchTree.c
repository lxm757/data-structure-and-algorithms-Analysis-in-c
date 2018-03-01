#include "SearchTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

/* Tree Node  */
struct TreeNode 
{
    ElementType Element;
    Position Left;
    Position Right;
};
 
/* Create and return new search tree  */
SearchTree Create( void )
{
    SearchTree T;
    T = ( SearchTree )malloc(
            sizeof( Position ) );
    if( T == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    *T = NULL;
    return T;
}

/* Make tree empty  */
void MakeEmpty( SearchTree T )
{
    if( T != NULL && *T != NULL )
    {
        MakeEmpty( &( *T )->Left );
        MakeEmpty( &( *T )->Right );
        free( *T );
        *T = NULL;
    }
}

/* Find Position of element X  */
static Position FindX( ElementType X, Position P )
{
    if( P == NULL )
    {
        return NULL;
    }
    else if( X < P->Element )
    {
        return FindX( X, P->Left );
    }
    else if( X > P->Element )
    {
        return FindX( X, P->Right );
    }
    else 
    {
        return P;
    }
}

/* Find position of X  */
Position Find( ElementType X, SearchTree T )
{
    if( T != NULL && *T != NULL )
    {
        return FindX( X, *T );
    }
    return NULL;
}

/* Find position of minimum element  */
static Position FindMinP( Position P )
{
    if( P == NULL )
    {
        return NULL;
    }
    else if( P->Left == NULL )
    {
        return P;
    }
    else 
    {
        return FindMinP( P->Left );
    }
}

/* Find position of minimum element, recursive  */
Position FindMin( SearchTree T )
{
    if( T != NULL && *T != NULL )
    {
        return FindMinP( *T );
    }
    return NULL;
}

/* Find Position of maximum element, no recursive  */
Position FindMax( SearchTree T )
{
    Position TmpP;
    TmpP = NULL;
    if( T != NULL && *T != NULL )
    {
        TmpP = *T;
        while( TmpP->Right != NULL )
        {
            TmpP = TmpP->Right;
        }
    }
    return TmpP;
}

/* Insert element X  */
/* Assume search tree T is legal  */
void Insert( ElementType X, SearchTree T )
{
    if( *T == NULL )
    {
        /* Create a one-node tree  */
        *T = ( Position )malloc(
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
void Delete( ElementType X, SearchTree T )
{
    Position TmpCell;
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
        else /* Found element to be deleted  */
        {
            /* Two children  */
            if( ( *T )->Left && ( *T )->Right )
            {
                TmpCell = FindMin( &( *T )->Right );
                ( *T )->Element = TmpCell->Element;
                Delete( ( *T )->Element, &( *T )->Right );
            }
            /* One right or zero children  */
            else if( ( *T )->Left == NULL )
            {
                TmpCell = *T;
                *T = ( *T )->Right;
                free( TmpCell );
            }
            /* One left children  */
            else if( ( *T )->Right == NULL )
            {
                TmpCell = *T;
                *T = ( *T )->Left;
                free( TmpCell );
            }
        }
    }
    else 
    {
        printf( "Element not found" );
    }
}

/* Retrieve element in position P  */
ElementType Retrieve( Position P )
{
    if( P != NULL )
    {
        return P->Element;
    }
    printf( "Illegal position" );
    exit( 1 );
    return 0; /* This 0 is used to avoid warning  */
}

/* Print tree in order  */
void PrintTree( SearchTree T )
{
    if( T != NULL && *T != NULL )
    {
        PrintTree( &( *T )->Left );
        printf( "%d\n", ( *T )->Element );
        PrintTree( &( *T )->Right );
    }
}

/* These follow functions use the type binary tree  */
/* But they can use to all type based binary tree  */

/* Count tree nodes  */
int CountNodes( SearchTree T )
{
    if( T != NULL && *T != NULL )
    {
        return CountNodes( &( *T )->Left ) +
            CountNodes( &( *T )->Right ) + 1;
    }
    else 
    {
        return 0;
    }
}

/* Count tree leaves  */
int CountLeaves( SearchTree T )
{
    if( T != NULL && *T != NULL )
    {
        if( ( *T )->Left == NULL && ( *T )->Right == NULL )
        {
            return 1;
        }
        else
        {
            return CountLeaves( &( *T )->Left ) 
                + CountLeaves( &( *T )->Right );
        }
    }
    else 
    {
        return 0;
    }
}

/* Count tree full nodes  */
int CountFull( SearchTree T )
{
    if( T != NULL && *T != NULL )
    {
        if( ( *T )->Left != NULL &&
                ( *T )->Right != NULL )
        {
            return 1 + CountFull( &( *T )->Left )
                + CountFull( &( *T )->Right );
        }
        else
        {
            return 0 + CountFull( &( *T )->Left )
                + CountFull( &( *T )->Right );
        }

        /* The same as  */
        /* return ( *T) ->Left != NULL && ( *T )->Right != NULL +  */
        /*      + CountFull( &( *T )->Left ) +  */
        /*      + CountFull( &( *T )->Right )  */
    }
    else 
    {
        return 0;
    }
}

/* Generates a uniform ramdom integer
 * in the appropriate closed interval  */
/* Assume Lower is smaller than Upper  */
static int RandInt( int Lower, int Upper )
{
    static int IsInitialized = 0;
    if( !IsInitialized )
    {
        srand( ( unsigned int )time( NULL ) );
        IsInitialized = 1;
    }
    return rand( ) % ( Upper - Lower + 1 ) + Lower;
}

/* Return NULL if N is not positive, 
 * or if N is so large that memory is exhausted  */
static Position MakeRandomTreeX( int Lower, int Upper )
{
    Position T;
    int RandomValue;

    T = NULL;
    if( Lower <= Upper )
    {
        T = ( Position )malloc( 
                sizeof( struct TreeNode ) ); 
        if( T != NULL )
        {
            T->Element = RandomValue = RandInt( Lower, Upper );    
            T->Left = MakeRandomTreeX( Lower, RandomValue - 1 );
            T->Right = MakeRandomTreeX( RandomValue + 1, Upper );
        }
        else 
        {
            printf( "Out of space !!!" );
        }
    }
    return T;
}

/* General fuction  */
SearchTree MakeRandomTree( int N, SearchTree T )
{
    if( T == NULL )
    {
        //SearchTree T;
        T = Create( );
        /* OK  */
    }
    if( *T == NULL )
    {
        *T = MakeRandomTreeX( 1, N );
    }
    return T;
}

/* One-dimensional range searching  */
/* Print X, K1 <= X <= K2  */
void PrintRange( ElementType Lower, ElementType Upper, SearchTree T )
{
    /* In order traversal  */
    if( T!= NULL && *T != NULL )
    {
        if( Lower < ( *T )->Element )
        {
            PrintRange( Lower, Upper, &( *T )->Left );
        }
        if( Lower <= ( *T )->Element && ( *T )->Element <= Upper )
        {
            printf( "%d\n", ( *T )->Element );
        }
        if( ( *T )->Element < Upper )
        {
            PrintRange( Lower, Upper, &( *T )->Right );
        }
    }
}

/* Return height of node,  */
/* Return < 0 if not found  */
int Depth( ElementType X, SearchTree T )
{
    if( T != NULL && *T != NULL )
    {
        if( X < ( *T )->Element )
        {
            return Depth( X, &( *T )->Left ) + 1;
        }
        else if( X > ( *T )->Element )
        {
            return Depth( X, &( *T )->Right ) + 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return INT_MIN;
    }
}

/* In order to print tree in level order 
 * we need a queue  */
/* Print tree in level order  */
void PrintInLevelOrder( SearchTree T )
{
    /* Declaration  */
    typedef struct TmpNode
    {
        Position P;
        struct TmpNode *Next;
    } *Node;

    Node Head, Rear;
    Node Tmp, TmpLeft, TmpRight;
    int NodeDepth;

    /* If T is a legal tree  */

    /* enqueue root  */
    Tmp = ( Node )malloc( 
            sizeof( struct TmpNode ) );
    if( Tmp == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    Tmp->P = *T;
    Tmp->Next = NULL;
    Head = Rear = Tmp;

    /* Repeatedly dequeue a node and enqueue its left
     * and right children (if any) until queue is empty  */
    NodeDepth = 0;
    while( Head != NULL )
    {
        /* dequeue a node  */
        Tmp = Head;
        Head = Head->Next;
        if( Head == NULL )
        {
            Rear = Head;
        }

        /* Print node element  */
        if( Depth( Retrieve( Tmp->P ), T ) != NodeDepth )
        {
            NodeDepth = Depth( Tmp->P->Element, T );
            printf( "\n" );
        }
        printf( "%d ", Retrieve( Tmp->P ) );
        
        //TmpLeft = TmpRight = NULL;
        /* Enqueue node left children if
         * left children is not null  */
        if( Tmp->P->Left != NULL )
        {
            /* Create temporary left node  */
            TmpLeft = ( Node )malloc( 
                    sizeof( struct TmpNode ) );
            if( TmpLeft == NULL )
            {
                printf( "Out of space !!!" );
                exit( 1 );
            }
            TmpLeft->P = Tmp->P->Left;
            TmpLeft->Next = NULL;
            /* Enqueue left node  */
            if( Head == NULL )
            {
                Head = Rear = TmpLeft;
            }
            else
            {
                Rear->Next = TmpLeft;
                Rear = TmpLeft;
            }
        }
        /* Enqueue node right children
         * if right children is not null  */
        if( Tmp->P->Right != NULL )
        {
            /* Create temporary right node  */
            TmpRight = ( Node )malloc( 
                    sizeof( struct TmpNode ) );
            if( TmpRight == NULL )
            {
                printf( "Out of space !!!" );
                exit( 1 );
            }
            TmpRight->P = Tmp->P->Right;
            TmpRight->Next = NULL;
            /* Enqueue right node  */
            if( Head == NULL )
            {
                Head = Rear = TmpRight;
            }
            else 
            {
                Rear->Next = TmpRight;
                Rear = TmpRight;
            }
        }

        free( Tmp );
    }
}

/* Count left blanks  */
/* Assume X, T are legal parameters  */
/* So can find element in tree whatever  */
static int CountLeftMargin( ElementType X, SearchTree T, int *Count )
{
    /* Declare sign, 1 for found; 0 not found  */
    int IsFound;

    if( *T != NULL )
    {
        /* Inorder traversal  */
        /* Traversal left children  */
        IsFound = CountLeftMargin( X, &( *T )->Left, Count );
        /* Return sign if found  */
        if( IsFound )
        {
            return 1; 
        }
        /* Else not found  */
        /* Count add one  */
        ++*Count;
        if( X == ( *T )->Element )
        {
            /* Return sign if found  */
            return 1;
        }
        /* Else not found  */
        /* Traversal right children  */
        return CountLeftMargin( X, &( *T )->Right, Count );
    } 
    else 
    {
        return 0;
    }
}

/* General interface  */
static int CountMargin( ElementType X, SearchTree T )
{
    int Count;
    Count = 0;
    if( T != NULL && *T != NULL )
    {
        if( CountLeftMargin( X, T, &Count ) <= 0 )
        {
            Count = 0;
        }
    }
    /* Illegal parameters  */
    return Count;
}

/* Print a tree in real type  */
void DrawTree( SearchTree T )
{
    /* Declaration  */
    typedef struct TmpNode
    {
        Position P;
        struct TmpNode *Next;
    } *Node;

    Node Head, Rear;
    Node Tmp, TmpLeft, TmpRight;
    int NodeDepth, Margin, Blank, i;

    /* Is a legal tree  */
    if( T == NULL || *T == NULL )
    {
        /* If not, do nothing  */
        return;
    }

    /* Enqueue root  */
    Tmp = ( Node )malloc( 
            sizeof( struct TmpNode ) );
    if( Tmp == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    Tmp->P = *T;
    Tmp->Next = NULL;
    Head = Rear = Tmp;

    /* Repeatedly dequeue a node and enqueue its left
     * and right children (if any) until queue is empty  */
    NodeDepth = 0;
    Margin = 0;
    while( Head != NULL )
    {
        /* dequeue a node  */
        Tmp = Head;
        Head = Head->Next;
        if( Head == NULL )
        {
            Rear = Head;
        }

        /* Print node element  */
        /* Is a new line  */
        if( Depth( Retrieve( Tmp->P ), T ) != NodeDepth )
        {
            /* Reset node depth  */
            NodeDepth = Depth( Tmp->P->Element, T );
            printf( "\n" );
            /* Reset margin  */
            Margin = 0;
        }

        /* Calculate left margin count  */
        Blank = CountMargin( Retrieve( Tmp->P ), T ) - Margin;

        /* Print blanks to fill margin  */
        for( i = 0; i < Blank * 2; i++ )
        {
            putchar( ' ' );
        }
        Margin += Blank + 1;
        
        /* Print element  */
        printf( "%2d", Retrieve( Tmp->P ) );

        /* Enqueue node left children if
         * left children is not null  */
        if( Tmp->P->Left != NULL )
        {
            /* Create temporary left node  */
            TmpLeft = ( Node )malloc( 
                    sizeof( struct TmpNode ) );
            if( TmpLeft == NULL )
            {
                printf( "Out of space !!!" );
                exit( 1 );
            }
            TmpLeft->P = Tmp->P->Left;
            TmpLeft->Next = NULL;
            /* Enqueue left node  */
            if( Head == NULL )
            {
                Head = Rear = TmpLeft;
            }
            else
            {
                Rear->Next = TmpLeft;
                Rear = TmpLeft;
            }
        }
        /* Enqueue node right children
         * if right children is not null  */
        if( Tmp->P->Right != NULL )
        {
            /* Create temporary right node  */
            TmpRight = ( Node )malloc( 
                    sizeof( struct TmpNode ) );
            if( TmpRight == NULL )
            {
                printf( "Out of space !!!" );
                exit( 1 );
            }
            TmpRight->P = Tmp->P->Right;
            TmpRight->Next = NULL;
            /* Enqueue right node  */
            if( Head == NULL )
            {
                Head = Rear = TmpRight;
            }
            else 
            {
                Rear->Next = TmpRight;
                Rear = TmpRight;
            }
        }

        free( Tmp );
    }
}

/* Compare two tree with structure  */
static int Similar( Position T1, Position T2 )
{
    if( T1 == NULL || T2 == NULL )
    {
        /* Both tree is empty, they are the same  */
        return T1 == NULL && T2 == NULL;
    }
    else
    {
        /* Both tree is not empty, they are the same,
         * compare left subtree and right subtree */
        return Similar( T1->Left, T2->Left )
            && Similar( T1->Right, T2->Right );
    }
}

/* Routine interface  */
int IsSimilar( SearchTree T1, SearchTree T2 )
{
    if( T1 == NULL || T2 == NULL )
    {
        /* Illegal parameters  */
        return -1;
    }
    return Similar( *T1, *T2 );
}

/* Compare two tree  */
/* Is two trees are isomorphic  */
static int Isomorphic( Position T1, Position T2 )
{
    if( T1 == NULL || T2 == NULL )
    {
        /* One or two of subtree is empty  */
        if( T1 == NULL && T2 == NULL )
        {
            /* Both subtree is empty,
             * they are the same  */
            return 1;
        }
        else
        {
            /* Only one of subtree is empty,
             * they are not the same */
            return 0;
        }
    }
    else  /* Both subtree is not empty  */
    {
        if( T1->Element == T2->Element )
        {
            /* Two node elements are equals,
             * compare t1 left subtree with t2 right subtree
             * and t1 right subtree with t2 left subtree; or
             * compare t1 left subtree with t2 left subtree
             * and t1 right subtree with t2 right subtree  */
            return ( Isomorphic( T1->Left, T2->Right ) 
                    && Isomorphic( T1->Right, T2->Left ) ) ||
                ( Isomorphic( T1->Left, T2->Left ) 
                  && Isomorphic( T1->Right, T2->Right ) );
        }
        else
        {
            return 0;
        }
    }
}

/* Common interface  */
int IsIsomorphic( SearchTree T1, SearchTree T2 )
{
    if( T1 == NULL || T2 == NULL )
    {
        /* Illegal parameters  */
        return -1;
    }
    return Isomorphic( *T1, *T2 );
}

#if 0 
/* Test  */
int main( void )
{
#if 0 
    SearchTree T;
    T = Create( );
    
    Insert( 11, T );
    Insert( 13, T );
    Insert( 19, T );
    Insert( 9 , T );
    Insert( 17, T );

    PrintTree( T );
    putchar( '\n' );

    printf( "Depth of 19: %d\n", Depth( 19, T ) );
    printf( "Depth of 17: %d\n", Depth( 17, T ) );
    printf( "Depth of not found: %d\n", Depth( 1, T ) );

    printf( "Tree nodes: %d\n",
            CountNodes( T ) );
    printf( "Tree leaves: %d\n",
            CountLeaves( T ) );
    printf( "Full leaves: %d\n",
            CountFull( T ) );

    Delete( 13, T );
    PrintTree( T );
    putchar( '\n' );

    printf( "Tree nodes: %d\n", 
            CountNodes( T ) );
    printf( "Tree leaves: %d\n", 
            CountLeaves( T ) );
    printf( "Full leaves: %d\n",
            CountFull( T ) );

    MakeEmpty( T );
    PrintTree( T );
    putchar( '\n' );

    if( T == NULL )
    {
        printf( "T is NULL\n" );
    }
    else if( *T == NULL )
    {
        printf( "*T is NULL\n" );
    }

    printf( "Create a random search tree:\n" );
    T = MakeRandomTree( 9, T );

    printf( "Level traversal: \n" );
    PrintInLevelOrder( T );
    putchar( '\n' );

    
    printf( "Draw tree: \n" );
    DrawTree( T );
    putchar( '\n' );
#endif

#if 1 
    SearchTree T1, T2;
    
    T1 = T2 = NULL;

    T1 = MakeRandomTree( 3, T1 );
    T2 = MakeRandomTree( 9, T2 );
    
    printf( "Tree1: \n" );
    DrawTree( T1 );
    printf( "\nTree2: \n" );
    DrawTree( T2 );

    
    printf( "\nthey %s similar\n", IsSimilar( T1, T2 ) ? 
            "are" : "are not" );
    printf( "\nthey are %s isomorphic\n", IsIsomorphic( T1, T2 ) ?
            "are" : "are not" ); 
#endif

    return 0;
}
#endif
