#include "StackP.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100

static int Buf[ BUFSIZE ];
static int Bufp = 0;

static int Getch( void );
static void IsLegal( int, Stack );
static void Ungetch( int );
static void Comment( void );
static void Character( int );
static void Printch( int Ch );

static int IsMatched = 1;
static int Line = 1;

struct ErrNode
{
    char *Arr;
    struct ErrNode *Next;
};

static struct ErrNode *ErrMsg;

void InsertMsg( char *);
void PrintMsg( struct ErrNode * );
void DeleteMsg( struct ErrNode * );

void PrintMsg( struct ErrNode *ErrMsg )
{
    struct ErrNode *TmpToNode;
    TmpToNode = ErrMsg;
    while( TmpToNode != NULL )
    {
        printf( "%s", TmpToNode->Arr );
        TmpToNode = TmpToNode->Next;
    }
}

void DeleteMsg( struct ErrNode * ErrMsg )
{
    struct ErrNode *TmpToNode;
    while( ErrMsg != NULL )
    {
        TmpToNode = ErrMsg;
        ErrMsg = ErrMsg->Next;
        free( TmpToNode->Arr );
        free( TmpToNode );
    }
}

void InsertMsg( char *Arr )
{
    struct ErrNode *Ptr;
    char *Msg = ( char * )malloc(
            sizeof( strlen( Arr ) ) );
    if( Msg == NULL )
    {
        printf( "Out of Space !!!" );
        exit( 1 );
    }
    strcpy( Msg, Arr );
    Ptr = ErrMsg;
    struct ErrNode *TmpToNode;
    TmpToNode = ( struct ErrNode * )malloc(
            sizeof( struct ErrNode ) );
    if( TmpToNode == NULL )
    {
        printf( "Out out space !!!" );
        exit( 1 );
    }
    TmpToNode->Arr = Msg;
    TmpToNode->Next = NULL;
    if( Ptr == NULL )
    {
        ErrMsg = TmpToNode;
    }
    else
    {
        while( Ptr->Next != NULL )
        {
            Ptr = Ptr->Next;
        }
        Ptr->Next = TmpToNode;
    }
}

/* Check program grammer  */
int main( void )
{
    Stack S = NULL;
    S = CreateStack( );
    int Ch;
    printf( "%3d ", 1 );
    while( ( Ch = Getch( ) ) != EOF )
    {
        if( Ch == '\'' || Ch == '"' )
        {
            Printch( Ch );
            /* Skip char and chars  */
            Character( Ch );
        }
        else if( Ch == '/' )
        {
            Printch( Ch );
            /* Is a comment  */
            Comment( );
        }
        else if( Ch == '(' || Ch == '[' || Ch == '{' ) 
        {
            Push( Ch, S );
            Printch( Ch );
        }
        else if( Ch == ')' || Ch == ']' || Ch == '}' )
        {
            Printch( Ch );
            IsLegal( Ch, S );
        }
        else
        {
            Printch( Ch );
        }
    }
    if( !IsEmptyStack( S ) )
    {
        IsMatched = 0;
    }

    if( IsMatched )
    {
        putchar( '\n' );
        printf( "Matched" );
        putchar( '\n' );
    }
    else
    {
        putchar( '\n' );
        printf( "Not Matched" );
        putchar( '\n' );
        PrintMsg( ErrMsg );
    }
    putchar( '\n' );

    DeleteMsg( ErrMsg );
    DisposeStack( S );
    return 0;
}

/* Skip character and string */
static void Character( int Ch )
{
    //printf( "character" );
    int TmpCh, NLine;
    char Lines[ 100 ];

    NLine = Line;
    while( ( TmpCh = Getch( ) ) != EOF )
    {
        putchar( TmpCh );
        if( TmpCh == '\\' )
        {
            putchar( Getch( ) );
        }
        else if( TmpCh == Ch )
        {
            break;
        }
    }
    if( TmpCh != Ch )
    {
        IsMatched = 0;
        sprintf( Lines, "At line %d\n", NLine );
        InsertMsg( Lines );
    }
}

/* Return true if matched  */
/* Otherwise return false  */
static void IsLegal( int Ch, Stack S )
{
    int Res, TmpCh, NLine;
    
    char Lines[ 100 ];
    NLine = Line;
    if( IsEmptyStack( S ) )
    {
        Res = 0;
    }
    else
    {
        TmpCh = Top( S );
        if( Ch == ')' )
        {
            Res = TmpCh == '(';    
        }
        else if( Ch == ']' )
        {
            Res = TmpCh == '[';
        }
        else
        {
            Res = TmpCh == '{';
        }
    }

    if( !Res )
    {
        IsMatched = 0;
        sprintf( Lines, "At line %d\n", NLine );
        InsertMsg( Lines );
    }
    else
    {
        Pop( S );
    }
}


/* Skip a comment  */
static void Comment( void )
{
    //printf( "Comment" );
    char Lines[ 100 ];
    int Ch, NLine;
    NLine = Line;
    if( ( Ch = Getch( ) ) != '*' )
    {
        /* Not a comment  */
        /* Put char back to input */
        Ungetch( Ch );
    }
    else
    {
        Printch( Ch );
        /* Is a comment  */
        /* Skip comment  */
        while( ( Ch = Getch( ) ) != EOF )
        {
            Printch( Ch );
            if( Ch == '*' )
            {
                if( ( Ch = Getch( ) ) != '/' )
                {
                    Ungetch( Ch );
                }
                else
                {
                    Printch( Ch );
                    break;
                }
            }
        }
        if( Ch != '/' )
        {
            IsMatched = 0;
            sprintf( Lines, "At line %d\n", NLine );
            InsertMsg( Lines );
        }
    }
}

/* Print char  */
static void Printch( int Ch )
{
    putchar( Ch );
    if( Ch == '\n' )
    {
        printf( "%3d ", Line );
    }
}

/* Get a char from stack  */
/* If stack is empty read new char  */
static int Getch( void )
{
    int Ch;
    if( Bufp > 0 )
    {
        if( Buf[ Bufp - 1 ] == '\n' )
        {
            Line++;
        }
        return Buf[ --Bufp ];
    }
    else
    {
        Ch = getchar( );
        if( Ch == '\n' )
        {
            Line++;
        }
        return Ch;
    }
}

/* Put a char into stack  */
static void Ungetch( int Ch )
{
    if( Ch == '\n' )
    {
        Line--;
    }
    if( Bufp < BUFSIZE )
    {
        Buf[ Bufp++ ] = Ch;
    }
    else 
    {
        printf( "Stack full, can't push" );
        exit( 1 );
    }
}
