#include "Polynomial.h"
#include <stdlib.h>
#include <stdio.h>

/* Test  */
int main( void )
{
    void AddPolynomial( const Polynomial, 
            const Polynomial, Polynomial );
    Polynomial Poly1, Poly2, Poly3;

    Poly1 = Create( );
    Poly2 = Create( );
    Poly3 = Create( );

    putchar( '\n' );
    InsertInOrder( 2, 1, Poly1 );
    InsertInOrder( 3, 4, Poly1 );
    InsertInOrder( 5, 9, Poly1 );
    InsertInOrder( 7, 11, Poly1 );
    printf( "Poly1: \n" );
    Print( Poly1 );

    putchar( '\n' );
    InsertInOrder( 3, 2, Poly2 );
    InsertInOrder( 6, 3, Poly2 );
    InsertInOrder( 8, 4, Poly2 );
    InsertInOrder( 11, 7, Poly2 );
    InsertInOrder( 12, 9, Poly2 );
    printf( "Poly2:\n" );
    Print( Poly2 );

    putchar( '\n' );
    AddPolynomial( Poly1, Poly2, Poly3 );
    Print( Poly3 );

    DeletePolynomial( Poly1 );
    DeletePolynomial( Poly2 );
    DeletePolynomial( Poly3 );

    return 0;
}

/* Add two polynomials  */
void AddPolynomial( const Polynomial Poly1, 
        const Polynomial Poly2, Polynomial PolySum )
{
    MakeEmpty( PolySum );    
    Item Item1, Item2, ItemS;

    Item1 = Poly1->Next;
    Item2 = Poly2->Next;
    ItemS = PolySum;
    
    while( Item1 != NULL && Item2 != NULL )
    {
        if( Item1->Exponent < Item2->Exponent )
        {
            Insert( Item1->Coefficient, 
                    Item1->Exponent, ItemS, PolySum );
            Item1 = Item1->Next;
        }
        else if( Item1->Exponent > Item2->Exponent ) 
        {
            Insert( Item2->Coefficient, 
                    Item2->Exponent, ItemS, PolySum );
            Item2 = Item2->Next;
        }
        else
        {
            Insert( Item1->Coefficient + Item2->Coefficient,
                    Item2->Exponent, ItemS, PolySum );
            Item1 = Item1->Next;
            Item2 = Item2->Next;
        }
        ItemS = ItemS->Next;
    }

    while( Item1 != NULL )
    {
        Insert( Item1->Coefficient, Item1->Exponent,
                ItemS, PolySum );
        Item1 = Item1->Next;
        ItemS = ItemS->Next;
    }
    while( Item2 != NULL )
    {
        Insert( Item2->Coefficient, Item2->Exponent,
                ItemS, PolySum );
        Item2 = Item2->Next;
        ItemS = ItemS->Next;
    }
}
