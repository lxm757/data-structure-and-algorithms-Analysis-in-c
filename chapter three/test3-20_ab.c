#include "StackP.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/* Priority  */
char Priority[ 100 ];

void InitializePriority( void );
void MiddleToReversePolish( char *, char * );
void InitializeArray( char *, int );

/* Test  */
int main( void )
{
    InitializePriority( );
    //char Arr[ 20 ] = "123 + 456 * 78 ";
    //char Arr[ 20 ] = " 123 + 456 * 78";
    //char Arr[ 20 ] = " 123 + 456 * 78 ";
    //char Arr[ 20 ] = "123+456*789";
    //char Arr[ 20 ] = "123+ 456*789 ";
    //char Arr[ 20 ] = "( 123 + 456 ) * 78 ";
    //char Arr[ 20 ] = "3 + 2 ^ 2 ";
    //char Arr[ 20 ] = "3 * 2 ^ 3 ";
    //char Arr[ 20 ] = "( 3 + 2 ) * 4 ";
    //char Arr[ 20 ] = "(3+2)*4";
    //char Arr[ 20 ] = "(3+2)*4 ";
    //char Arr[ 20 ] = "1 - 2 + 3 ";
    char Arr[ 20 ] = "2 ^ 2 ^ 3 ";
    //printf( "%s\n", Arr );
    char Res[ 20 ];

    /* Initialize array  */
    InitializeArray( Res, 20 );

    MiddleToReversePolish( Arr, Res );

    printf( "%s\n", Res );

    return 0; 
}

/* Initialize priority table  */
void InitializePriority( void )
{
    /* low to high  */
    Priority[ (int)'(' ] = 'A';
    Priority[ (int)'+' ] = 'B';
    Priority[ (int)'-' ] = 'C';
    Priority[ (int)'*' ] = 'D';
    Priority[ (int)'/' ] = 'D';
    Priority[ (int)'%' ] = 'D';
    Priority[ (int)'^' ] = 'E';
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

/* middle to reverse polish  */
void MiddleToReversePolish( char *Middle,
        char *ReversePolish )
{
    Stack S;
    S = CreateStack( );
    int Ch, i;
    char Digit[ 20 ];
    /* Initialize array  */
    InitializeArray( Digit, 20 );
    while( ( Ch = *Middle++ ) != '\0' )
    {
        /* Skip space  */
        while( Ch == ' ')
        {
            Ch = *Middle++;
        }
        //putchar( Ch );
        /* Is a digit  */
        if( isdigit( Ch ) )
        {
            for( i = 0; i < 20 && isdigit( Ch ); i++ )
            {
                Digit[ i ] = Ch;
                Ch = *Middle++;
            }
            Digit[ i++ ] = ' ';
            Digit[ i ] = '\0';
            strcat( ReversePolish, Digit );
            Middle--;
        }
        else if( Ch == '(' )
        {
            Push( Ch, S );
        }
        else if( Ch == ')' )
        {
            /* Wrong  */
            while( ( Ch = TopAndPop( S ) ) != '(' ) 
            {
                Digit[ 0 ] = Ch;
                Digit[ 1 ] = ' ';
                Digit[ 2 ] = '\0';
                strcat( ReversePolish, Digit );
            }
        }
        else if( Ch == '\0' )
        {
            break;
        }
        else 
        {
            if( IsEmptyStack( S ) )
            {
                Push( Ch, S );
            }
            else 
            {
                while( !IsEmptyStack( S ) && 
                        Priority[ Top( S ) ] > Priority[ Ch ] )
                {
                    Digit[ 0 ] = TopAndPop( S );
                    Digit[ 1 ] = ' ';
                    Digit[ 2 ] = '\0';
                    strcat( ReversePolish, Digit );
                }
                Push( Ch, S );
            }
        }
    }
    while( !IsEmptyStack( S ) )
    {
        Digit[ 0 ] = TopAndPop( S );
        Digit[ 1 ] = ' ';
        Digit[ 2 ] = '\0';
        strcat( ReversePolish, Digit );
    }
}
