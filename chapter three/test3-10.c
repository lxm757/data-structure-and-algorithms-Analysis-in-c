#include "DoubleCircleLinkedListP.h"
#include <stdio.h>

#define MEMBER 5
#define COUNT  2

/* Test  */
int main( void )
{
    int Josephus( DCList, int, int );
    
    DCList L = NULL;
    int i;

    L = Create( L );

    for( i = 1; i <= MEMBER; i ++ )
    {
        Insert( i, Last( L ), L );
    }

    printf( "Josephus %d %d\n", MEMBER, COUNT );
    Josephus( L, MEMBER, COUNT );

    DeleteList( L );

    return 0;
}

/* Josephus question  */
int Josephus( DCList L, int N, int M )
{
    Position GetOutOf( Position, DCList, int );
    Position P;
    int Num;
    P = First( L );
    while( !IsLast( P, L ) || !IsFirst( P, L ) )
    {
        Print( L );
        Num = M % N--;
        P = GetOutOf( P, L, Num );
    }
    printf( "Josephus %d\n", Retrieve( P ) );
    return 0;
}

/* Delete number and return new position  */
Position GetOutOf( Position P, DCList L, int Num )
{
    while( Num-- >= 0 )
    {
        P = Advance( P );
    }
    printf( "Get out of %d\n", Retrieve( Previous( P ) ) );
    DeletePosition( Previous( P ), L );
    return P;
}

