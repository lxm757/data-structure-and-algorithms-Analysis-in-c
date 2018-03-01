#include "Polynomial.h"
#include <stdlib.h>
#include <stdio.h>

/* Test  */
int main( void )
{
    void MultiplyPolynomials( const Polynomial,
            const Polynomial, Polynomial );
    Polynomial Poly1, Poly2, Poly3;

    Poly1 = Create( );
    Poly2 = Create( );
    Poly3 = Create( );

    putchar( '\n' );
    InsertInOrder( 2, 1, Poly1 );
    InsertInOrder( 3, 4, Poly1 );
    //InsertInOrder( 5, 9, Poly1 );
    //InsertInOrder( 7, 11, Poly1 );
    printf( "Poly1: \n" );
    Print( Poly1 );

    putchar( '\n' );
    InsertInOrder( 3, 2, Poly2 );
    InsertInOrder( 6, 3, Poly2 );
    //InsertInOrder( 8, 4, Poly2 );
    //InsertInOrder( 11, 7, Poly2 );
    //InsertInOrder( 12, 9, Poly2 );
    printf( "Poly2:\n" );
    Print( Poly2 );

    putchar( '\n' );
    MultiplyPolynomials( Poly1, Poly2, Poly3 );
    printf( "Poly3:\n" );
    Print( Poly3 );

    DeletePolynomial( Poly1 );
    DeletePolynomial( Poly2 );
    DeletePolynomial( Poly3 );
    
    return 0;
}


/* Multiple two Polynomials  */
void MultPolynomial( const Polynomial Poly1, 
        const Polynomial Poly2, Polynomial PolySum )
{
    MakeEmpty( PolySum );
    Item Item1, Item2;

    Item1 = Poly1->Next;

    while( Item1 != NULL )
    {
        Item2 = Poly2->Next;
        while( Item2 != NULL )
        {
            InsertInOrder( Item1->Coefficient * Item2->Coefficient, 
                    Item1->Exponent + Item2->Exponent, PolySum );
            Item2 = Item2->Next;
        }
        Item1 = Item1->Next;
    }
}

static void AddToPolynomial( const Polynomial Poly1,
        const Polynomial PolySum )
{
    Item Item1, Item2, ItemSum;
    Item1 = Poly1->Next;
    Item2 = PolySum->Next;
    ItemSum = PolySum;

    while( Item1 != NULL && Item2 != NULL )
    {
        if( Item1->Exponent < Item2->Exponent )
        {
            Insert( Item1->Coefficient,
                    Item1->Exponent, ItemSum, PolySum );
            Item1 = Item1->Next;
            ItemSum = ItemSum->Next;
        }
        else if( Item1->Exponent > Item2->Exponent )
        {
            Insert( Item2->Coefficient,
                    Item2->Exponent, ItemSum, PolySum );
            ItemSum = ItemSum->Next;
            Item2 = Item2->Next;
            DeleteAfter( ItemSum, PolySum );
        }
        else
        {
            Item2->Coefficient += Item1->Coefficient;
            Item2 = Item2->Next;
            Item1 = Item1->Next;
            ItemSum = ItemSum->Next;
        }
    }

    while( Item1 != NULL )
    {
        Insert( Item1->Coefficient, Item1->Exponent, 
                ItemSum, PolySum );
        Item1 = Item1->Next;
        ItemSum = ItemSum->Next;
    }
}

/* Multiple two polynomial  */
void MultiplyPolynomials( const Polynomial Poly1,
        const Polynomial Poly2, Polynomial PolySum )
{
    MakeEmpty( PolySum );
    Item Item1, Item2, Item3;
    Polynomial Poly3;

    Item1 = Poly1->Next;
    Poly3 = Create( );

    while( Item1 != NULL )
    {
        Item2 = Poly2->Next;
        Item3 = Poly3;
        MakeEmpty( Poly3 );
        while( Item2 != NULL )
        {
            Insert( Item1->Coefficient * Item2->Coefficient,
                    Item1->Exponent + Item2->Exponent,
                    Item3, Poly3 );
            Item2 = Item2->Next;
            Item3 = Item3->Next;
        }
        AddToPolynomial( Poly3, PolySum );
        Item1 = Item1->Next;
    }
}
