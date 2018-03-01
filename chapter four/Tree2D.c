#include "Tree2D.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* Change keys to use k-tree  */
#define KEYS ( 2 )

/* Struct  */
struct TreeNode
{
    Key Keys[ KEYS ];
    Position Left;
    Position Right;
};

/* Create and return new 2d tree  */
Tree2D Create( Tree2D T )
{
    if( T == NULL )
    {
        T = ( Tree2D )malloc(
                sizeof( Position ) );
        if( T == NULL )
        {
            printf( "Out of space !!!" );
            exit( 1 );
        }
        *T = NULL;
    }
    /* return T is not empty  */
    return T;
}

/* Make tree empty  */
void MakeEmpty( Tree2D T )
{
    int i;
    if( T != NULL && *T != NULL )
    {
        MakeEmpty( &( *T )->Left );
        MakeEmpty( &( *T )->Right );
        /* Free keys  */
        for( i = 0; i < KEYS; i++ )
        {
            if( ( *T )->Keys[ i ] )
            {
                /* Free key if key is not empty  */
                free( ( *T )->Keys[ i ] );
            }
        }
        free( *T );
        /* Remember set empty  */
        *T = NULL;
    }
}

/* Dispose tree  */
Tree2D Dispose( Tree2D T )
{
    MakeEmpty( T );
    free( T );
    return NULL;
}

/* Get keys from input string  */
/* Assume legal parameter used  */
static Position SplitAndGetKey( ElementType Str, Position P )
{
    Key KeyPos;
    int i;
    /* Initialized  */
    for( i = 0; i < KEYS; i++ )
    {
        P->Keys[ i ] = NULL;
    }
    /* Get keys  */
    KeyPos = strtok( Str, " " );
    for( i = 0; i < KEYS && KeyPos; i++ )
    {
        P->Keys[ i ] = ( Key )malloc(
                sizeof( char ) * strlen( KeyPos ) + 1 );
        if( P->Keys[ i ] == NULL )
        {
            printf( "Out of space !!!" );
            exit( 1 );
        }
        strcpy( P->Keys[ i ], KeyPos );
        KeyPos = strtok( NULL, " " );
    }
    P->Left = P->Right = NULL;
#if 0
    printf( "Middle\n" );
    printf( "i = %d\n", i );
    printf( "KeyPos = %s\n", KeyPos == NULL ?
            "NULL" : "NOT NULL" );
#endif
    /* Make sure all keys get */
    if( i < KEYS || KeyPos != NULL )
    {
        /* Illegal paramters  */
        printf( "Illgeal input" );

        /* The process will do this first,
         * then print err, why ???  */
        MakeEmpty( &P );
    }
    return P;
}

/* Insert new node by element  */
/* Assume legal parameter used  */
static void InsertStr( ElementType Str, Tree2D T, int *Count )
{
    Key KeyPos, TmpStr;
    int i;
    if( *T == NULL )
    {
        *T = ( Position )malloc( 
                sizeof( struct TreeNode ) );
        if( *T == NULL )
        {
            printf( "Out of space !!!" );
            exit( 1 );
        }
        /* Split input string into two keys  */
        if( Str != NULL )
        {
            *T = SplitAndGetKey( Str, *T );
        }
    }
    else
    {
        /* Compare with Key  */
        /* Let N is *Count  */
        /* if   N % KEYS == k   compare with Key[ k ]  */
        /* Keep str int new string  */
        /* Function strtok may destory string  */
        TmpStr = ( Key )malloc( 
                sizeof( char ) * strlen( Str ) + 1 );
        if( TmpStr == NULL )
        {
            printf( "Out of space !!!" );
            exit( 1 );
        }
        strcpy( TmpStr, Str );
        /* Get key  */
        KeyPos = strtok( Str, " " );
        for( i = 0; i < ( *Count % KEYS ); i++ )
        {
            KeyPos = strtok( NULL, " " );
        }
        /* Compare  */
        if( strcmp( KeyPos, ( *T )->Keys[ *Count % KEYS ] ) < 0 )
        {
            /* Insert key in left subtree  */
            ++*Count;
            InsertStr( TmpStr, &( *T )->Left, Count );
        }
        else if( strcmp( KeyPos, ( *T )->Keys[ *Count % KEYS ] ) > 0 )
        {
            /* Insert key in right subtree  */
            ++*Count;
            InsertStr( TmpStr, &( *T )->Right, Count );
        }
        /* Else key is in the tree, do nothing  */
        /* The key[ i ] is unique  */
    }
}

void Insert( ElementType Str, Tree2D T )
{
    int Count;
    Count = 0;
    if( T != NULL )
    {
        InsertStr( Str, T, &Count );
    }
    else
    {
        printf( "Illegal parameter" );
    }
}

/* Print all keys  */
void PrintKeys( Position P )
{
    int i;
    if( P != NULL )
    {
        for( i = 0; i < KEYS; i++ )
        {
            printf( "%s%s", P->Keys[ i ], 
                    i == KEYS - 1 ? "" : " " );
        }
    }
}

/* Print Tree by in order  */
void PrintTree( Tree2D T )
{
    if( T != NULL && *T != NULL )
    {
        PrintTree( &( *T )->Left );
        PrintKeys( *T );
        printf( "\n" );
        PrintTree( &( *T )->Right );
    }
}

/* Is a node in range  */
int IsFound( Position P, Key Lower[ ], Key Upper[ ] )
{
    int i, IsFound;
    IsFound = 1;
    if( P != NULL )
    {
        /* Is node keys suit for all ranges  */
        for( i = 0; i < KEYS; i++ )
        {
            if(  !( strcmp( P->Keys[ i ], Lower[ i ] ) >= 0 
                   && strcmp( P->Keys[ i ], Upper[ i ] ) <= 0 ) ) 
            {
                IsFound = 0;
            }
        }
    }
    else
    {
        IsFound = 0;
    }
    return IsFound;
}

#if 1
/* Two-dimensional range searching  */
/* PrintRange( T, low1, up1, low2, up2 )  */
/* Assume legal parameter used  */
static void PrintRangeX( Position T, int Count, 
        Key Lower[ KEYS ], Key Upper[ KEYS ] )
{
    int nKey;
    nKey = Count % KEYS;
    if( T != NULL )
    {

        /* Key > lower  */
        if( strcmp( Lower[ nKey ], T->Keys[ nKey ] ) < 0  )
        {
            PrintRangeX( T->Left, Count + 1, Lower, Upper );
        }

        /* Is lower <= key <= upper  */
        if( IsFound( T, Lower, Upper ) )
        {
            PrintKeys( T );
            putchar( '\n' );
        }

        /* Key < upper  */
        if( strcmp( T->Keys[ nKey ], Upper[ nKey ] ) < 0 )
        {
            PrintRangeX( T->Right, Count + 1, Lower, Upper );
        }
    }
}

void PrintRange( Tree2D T, ... )
{
    /* Get paramters  */
    int i;
    va_list Ap;
    Key Lower[ KEYS ];
    Key Upper[ KEYS ];

    /* Get lows nad ups  */
    va_start( Ap, T );
    for( i = 0; i < KEYS; i++ )
    {
        Lower[ i ] = va_arg( Ap, char * );
        Upper[ i ] = va_arg( Ap, char * );
    }
    
    if( T != NULL )
    {
        PrintRangeX( *T, 0, Lower, Upper );
    }
}
#endif

#if 0 
/* Test  */
int main( void )
{
    Tree2D T = NULL;
    T = Create( T );
    
    char Str[ 128 ];
#if 1
    /* 2 tree  */

    strcpy( Str, "Harry Truman" );
    printf( "Insert \"%s\" ", Str );
    Insert( Str, T );
    putchar( '\n' );

    strcpy( Str, "Dwight Eisenhower" );
    //strcpy( Str, "Dwight" );
    printf( "Insert \"%s\" ", Str );
    Insert( Str, T );
    putchar( '\n' );

    strcpy( Str, "John Kennedy" );
    printf( "Insert \"%s\" ", Str );
    Insert( Str, T );
    putchar( '\n' );

    strcpy( Str, "Lyndon Johnson" );
    printf( "Insert \"%s\" ", Str );
    Insert( Str, T );
    putchar( '\n' );

    strcpy( Str, "Richard Nixon" );
    printf( "Insert \"%s\" ", Str );
    Insert( Str, T );
    putchar( '\n' );

    strcpy( Str, "Gerald Ford" );
    printf( "Insert \"%s\" ", Str );
    Insert( Str, T );
    putchar( '\n' );

    strcpy( Str, "Jimmy Carter" );
    printf( "Insert \"%s\" ", Str );
    Insert( Str, T );
    putchar( '\n' );

    strcpy( Str, "Ronald Reagan" );
    printf( "Insert \"%s\" ", Str );
    Insert( Str, T );
    putchar( '\n' );

    strcpy( Str, "George Bush" );
    printf( "Insert \"%s\" ", Str );
    Insert( Str, T );
    putchar( '\n' );

    strcpy( Str, "Bill Clinton" );
    printf( "Insert \"%s\" ", Str );
    Insert( Str, T );
    putchar( '\n' );
    
    putchar( '\n' );
#endif

    PrintTree( T );
    putchar( '\n' );

    PrintRange( T, "Dwight", "Richard", "Ford", "Reagan" );

    return 0;
}

#endif
