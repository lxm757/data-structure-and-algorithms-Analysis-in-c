#include "Polynomial.h"
#include <stdio.h>

/* Test  */
int main( void )
{
    void PowPolynomial( Polynomial P, 
            int N, Polynomial PolySum );

    Polynomial Poly1, Poly2;
    Poly1 = Create( );
    Poly2 = Create( );

    InsertInOrder( 2, 1, Poly1 );
    InsertInOrder( 3, 4, Poly1 );
    printf( "Poly1: \n" );
    Print( Poly1 );

    putchar( '\n' );
    PowPolynomial( Poly1, 2 , Poly2 );
    printf( "Poly2:\n" );
    Print( Poly2 );

    DeletePolynomial( Poly1 );
    DeletePolynomial( Poly2 );
 
    return 0;
}

//static int IsEven( int N )
//{
//    return N % 2 == 0;
//}
//
///* Pow with Polynomial  */
//void PowPolynomial( Polynomial P, int N, 
//        Polynomial PolySum )
//{
//    Polynomial Tmp;
//    Tmp = Create( );
//    MakeEmpty( Tmp );
//    if( N == 0 )
//    {
//
//    }
//    else if( N == 1 )
//    {
//        Copy( P, PolySum );            
//        printf( "Copyed\n" );
//    }
//    else if( IsEven( N ) )
//    {
//        MultiplyPolynomial( P, P, Tmp );
//        PowPolynomial( Tmp, N / 2, PolySum );
//    }
//    else
//    {
//        MultiplyPolynomial( P, P, Tmp );
//        PowPolynomial( Tmp, N / 2, PolySum );
//        MakeEmpty( Tmp );
//        Copy( PolySum, Tmp );
//        MultiplyPolynomial( Tmp, P, PolySum );
//    }
//
//    DeletePolynomial( Tmp );
//}
