#include "Polynomial.h"
#include <stdio.h>
#include <stdlib.h>

///* Test  */
//int main( void )
//{
//    Polynomial P;
//    P = Create( );
//    InsertInOrder( 3, 2, P );
//    InsertInOrder( 4, 8, P );
//    InsertInOrder( 5, 7, P );
//    //DeletePolynomial( P );
//    Print( P );
//    return 0;
//}

/* Create header for Polynomial  */
/* Header implementation assumed  */
/* Parameter P is unused in thsi implementation  */
static Polynomial Header( Polynomial P )
{
    Item Itm;
    Itm = ( Item )malloc( sizeof( struct Node) );
    if( Itm == NULL )
    {
        printf( "Can't allocated" );
    }
    Itm->Coefficient = 0;
    Itm->Exponent = 0;
    Itm->Next = NULL;
    return Itm;
} 

/* Create and return new Polynomial  */
Polynomial Create( void )
{
    return Header( NULL );
}

/* Delete all items except for header  */
/* P is not NULL  */
void MakeEmpty( Polynomial P )
{
    Item Itm;
    while( P->Next != NULL )
    {
        Itm = P->Next;
        P->Next = P->Next->Next;
        free( Itm );
    }
}

/* Delete Polynomial  */
void DeletePolynomial( Polynomial P )
{
    MakeEmpty( P );
    free( P );
    P = NULL;
}

/* Delete (after legal Item) */
/* Parameter P is unused in this implementation  */
void DeleteAfter( Item Itm, Polynomial P )
{
    Item TmpCell;
    if( Itm->Next != NULL )
    {
        TmpCell = Itm->Next;
        Itm->Next = TmpCell->Next;
        free( TmpCell );
    }    
}

/* Insert Item into Ploynomial  */
/* After legal Item I  */
/* Parameter P is unused in this implemetation  */
void Insert( int Coefficient, int Exponent, 
        Item I, Polynomial P )
{
    Item TmpCell;

    TmpCell = ( Item )malloc(
            sizeof( struct Node ) );
    if( TmpCell == NULL )
    {
        printf( "Out of space !!!" );
        exit( 1 );
    }
    TmpCell->Coefficient = Coefficient;
    TmpCell->Exponent = Exponent;

    if( I->Next != NULL && I->Next->Exponent == Exponent )
    {
        I->Next->Coefficient += Coefficient;
        free( TmpCell );
    }
    else
    {
        TmpCell->Next = I->Next;
        I->Next = TmpCell;
    }
}

/* Binary search and return right position before
 * inert item  */
static Item PrevInsertPosition( int Exponent, 
       Polynomial P )
{
    //printf( "Find Prev Position\n" );
    while( P->Next != NULL )
    {
        if( P->Next->Exponent >= Exponent )
        {
            break;
        }
        P = P->Next;
    }
    //printf( "Found Prev Position\n" );
    return P;
} 

/* Insert in order  */
/* After legal Item I  */
void InsertInOrder( int Coefficient, int Exponent, 
        Polynomial P )
{
    //printf( "Insert In Order\n" );
    Item Prev = PrevInsertPosition( Exponent, P );
    Insert( Coefficient, Exponent, Prev, P );
}

/* Print Ploynomial  */
void Print( Polynomial P )
{
    while( P->Next != NULL )
    {
        printf( "%d^%d\n", P->Next->Coefficient, 
                P->Next->Exponent );
        P = P->Next;
    }
}

/* Add two Polynomials  */
void AddPolynomial( const Polynomial Poly1, 
        const Polynomial Poly2, Polynomial PolySum )
{
    MakeEmpty( PolySum );
    Item Item1, Item2, ItemS;
    Item1 = Poly1->Next;
    Item2 = Poly2->Next;
    ItemS = PolySum;

    while( Item1 != NULL || Item2 != NULL )
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
            Item2 = Item2->Next;
            ItemSum = ItemSum->Next;
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
void MultiplyPolynomial( const Polynomial Poly1,
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

/* Copy poly1 to poly2  */
void Copy( Polynomial Poly1, Polynomial Poly2 )
{
    Item Item1, Item2;
    Item1 = Poly1->Next;
    Item2 = Poly2;
    while( Item1 != NULL )
    {
        Insert( Item1->Coefficient,
                Item1->Exponent, Item2, Poly2 );
        Item1 = Item1->Next;
        Item2 = Item2->Next;
    }
}

/* Is number N is even  */
static int IsEven( int N )
{
    return N % 2 == 0;
}

/* Pow with Polynomial  */
/* Recure implementation  */
void PowPolynomial( Polynomial P, int N, 
        Polynomial PolySum )
{
    Polynomial Tmp;
    Tmp = Create( );
    MakeEmpty( Tmp );
    if( N == 0 )
    {

    }
    else if( N == 1 )
    {
        Copy( P, PolySum );            
        printf( "Copyed\n" );
    }
    else if( IsEven( N ) )
    {
        MultiplyPolynomial( P, P, Tmp );
        PowPolynomial( Tmp, N / 2, PolySum );
    }
    else
    {
        MultiplyPolynomial( P, P, Tmp );
        PowPolynomial( Tmp, N / 2, PolySum );
        MakeEmpty( Tmp );
        Copy( PolySum, Tmp );
        MultiplyPolynomial( Tmp, P, PolySum );
    }

    DeletePolynomial( Tmp );

}
