#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "StackP.h"

/* Test  */
int main( void )
{
    int ReversePolish( char * );
    int Result;
    char Equation[ ] = 
        "123 234 + 34 45 * +";
    Result = ReversePolish( Equation );
    printf( "%d\n", Result );
    return 0;
}

/* Calculate two digit  */
int Calculate( char Ch, int Top1, int Top2 )
{
    int Result;
    switch ( Ch )
    {
        case '+':
           Result = Top1 + Top2;
           //printf( "%d + %d\n", Top1, Top2 );
           break;
        case '-':
           Result = Top1 - Top2;
           //printf( "%d - %d\n", Top1, Top2 );
           break; 
        case '*':
           Result = Top1 * Top2;
           //printf( "%d * %d\n", Top1, Top2 );
           break;
        case '/':
           Result = Top1 / Top2;
           //printf( "%d / %d\n", Top1, Top2 );
           break;
        default:
           printf( "Illegal Option %c\n", Ch );
           exit( 1 );
           break;
    }
    return Result;
}


/* Calculcate reverse polish equation  */
int ReversePolish( char *Polish )
{
    Stack S;
    S = CreateStack( );
    int Ch, i;
    char Digit[ 20 ];
    while ( ( Ch = *Polish++ ) != '\0' )
    {
        /* Skip space  */
        while( Ch == ' ' )
        {
            Ch = *Polish++;
        }
        /* Is a digit  */
        if( isdigit( Ch ) )
        {
            for( i = 0; i < 20 && isdigit( Ch ); i++ )
            {
                Digit[ i ] = Ch;
                Ch = *Polish++;
            }
            Digit[ i ] = '\0';
            Push( atoi( Digit ), S );
            //printf( "%d\n", atoi( Digit ) );
        }
        else 
        {
            i = TopAndPop( S );
            i = Calculate( Ch , TopAndPop( S ), i );
            Push( i, S );
        }
    }
    return TopAndPop( S );
    DisposeStack( S );
}
