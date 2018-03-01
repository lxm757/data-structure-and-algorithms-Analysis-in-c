#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct Node
{
    char *Arr;
    struct Node *Next;
} *PtrToNode;

typedef PtrToNode Stack;
typedef PtrToNode Position;

/* Is a stack empty  */
int IsEmpty( Stack S )
{
    return S->Next == NULL;
}

/* Create and return a header  */
Stack Create( void )
{
    Stack S; 
    S = ( PtrToNode )malloc( 
            sizeof( struct Node ) );
    S->Arr = NULL;
    S->Next = NULL;
    return S;
}

/* Return cell value and delete cell  */
char *Pop( Stack S )
{
    PtrToNode P;
    char *Tmp;
    Tmp = NULL;
    if( !IsEmpty( S ) )
    {
        P = S->Next;
        S->Next = P->Next;
        Tmp = P->Arr;
        free( P );
    }
    return Tmp;
}

/* Push value into stack  */
void Push( char *Arr, Stack S )
{
    char *Tmp;
    PtrToNode P;
    P = ( PtrToNode )malloc(
            sizeof( struct Node ) );
    Tmp = ( char * )malloc(
            sizeof( strlen( Arr ) + 1 ) );
    if( Tmp == NULL || P == NULL )
    {
        printf( "Out out space !!!" );
        exit( 1 );
    }

    strcpy( Tmp, Arr );
    P->Arr = Tmp;
    P->Next = NULL;

    P->Next = S->Next;
    S->Next = P;
}

/* Dispose stack  */
void Dispose( Stack S )
{
    if( !IsEmpty( S ) )
    {
        free( Pop( S ) );
    }
    free( S );
}

void ReversePolishToMiddle( char *, char * );

/* Test  */
int main( void )
{
    char ReversePolish[ ] = "1 2 + 3 *";
    char Arr[ strlen( ReversePolish ) + 1 ];

    printf( "%s\n", ReversePolish );
    
    ReversePolishToMiddle( ReversePolish, Arr );

    printf( "%s\n", Arr );

    return 0;
}

/* Initialize array  */
void InitializeArray( char *Arr, int Size )
{
    int i;
    for( i = 0; i < Size; i++ )
    {
        Arr[ i ] = '\0';
    }
}

/* Calculate two members  */
void Calculate( int Ch, Stack S )
{
    int Size;
    char *P1, *P2, *Tmp;

    P2 = Pop( S );
    P1 = Pop( S );
    Size = strlen( P1 ) + strlen( P2 ) + 8;

    Tmp = ( char * )malloc( Size );
    InitializeArray( Tmp, Size );

    if( Tmp == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }

    sprintf( Tmp, "( %s%c %s) ", P1, Ch, P2 );

    //printf( "%s\n", Tmp );
    
    Push( Tmp, S );
    free( Tmp );
}

/* Reverse polish to middle  */
void ReversePolishToMiddle( char *ReversePolish,
        char *Middle )
{
    Stack S;
    S = Create( );
    int Ch, i;
    char Digit[ 20 ];
    InitializeArray( Digit, 20 );
    
    while( ( Ch = *ReversePolish++ ) != '\0' )
    {
        /* Skip space  */
        while( Ch == ' ' )
        {
            Ch = *ReversePolish++;
        }
        /* Is a digit  */
        if( isdigit( Ch ) )
        {
            for( i = 0; i < 20 && isdigit( Ch ); i++ )
            {
                Digit[ i ] = Ch;
                Ch = *ReversePolish++;
            }
            Digit[ i++ ] = ' ';
            Digit[ i ] = '\0';
            Push( Digit, S );
        }
        else if( Ch == '\0' )
        {
            break;
        }
        else
        {
            Calculate( Ch, S );
        }
    }
    
    strcpy( Middle, Pop( S ) );
    Dispose( S );
        
}
