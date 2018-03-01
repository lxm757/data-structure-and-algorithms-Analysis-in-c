#ifndef _Polynomial_H

typedef struct Node *PtrToNode;

struct Node 
{
    int Coefficient;
    int Exponent;
    PtrToNode Next;
};

/* Nodes sorted by exponent  */
typedef PtrToNode Polynomial;
typedef PtrToNode Item;

Polynomial Create( void );
void MakeEmpty( Polynomial P );
void DeletePolynomial( Polynomial P );
void DeleteAfter( Item Itm, Polynomial P );
void Insert( int Coefficient, int Exponent, 
       Item I, Polynomial P );
void InsertInOrder( int Coefficient, int Exponent, 
        Polynomial P );
void Print( Polynomial P );
void AddPolynomial( Polynomial Poly1,
        Polynomial Poly2, Polynomial PolySum );
void MultiplyPolynomial( 
        const Polynomial Poly1,
        const Polynomial Poly2,
        Polynomial PolySum );
void Copy( Polynomial Poly1, Polynomial Poly2 );
void PowPolynomial( Polynomial P, int N,
        Polynomial PolySum );

#endif
