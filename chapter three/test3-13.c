#include "LinkedListP.h"
#include <stdlib.h>
#include <stdio.h>

/* Radix Sort  */

/* Test  */
int main( void )
{
    void Radixs( int [ ], int, int, int );

    /* The range of number is 0 to 999  */
    /* Bucket size is 10  */
    /* Array size is 10  */
    /* Sort count is 3  */
    int Numeric[ 10 ];
    Numeric[ 0 ] = 64;
    Numeric[ 1 ] = 8;
    Numeric[ 2 ] = 216;
    Numeric[ 3 ] = 512;
    Numeric[ 4 ] = 27;
    Numeric[ 5 ] = 729;
    Numeric[ 6 ] = 0;
    Numeric[ 7 ] = 1;
    Numeric[ 8 ] = 343;
    Numeric[ 9 ] = 125;

    int ArraySize = 10;
    int SortCount = 1;
    int BucketSize = 1000;

    Radixs( Numeric, ArraySize, SortCount, BucketSize );

    return 0;
}

/* Print array  */
void PrintArr( List Arr[], int Size )
{
    int i;
    for( i = 0; i < Size; i++ )
    {
        printf( "%4d | ", i );
        Print( Arr[ i ] );        
        putchar( '\n' );
    }
}

/* Radix Sort  */
/* Size is Numeric[ ] size  */
/* Count is Sort counts  */
/* NBucket is bucket size  */
void Radixs( int Numeric[ ], int Size, int Count, int NBucket )
{
    int i, j, Num;
    List Tmp;
    Position P;
    
    List Bucket[ NBucket ];

    /* Create buckets  */
    for( i = 0; i < NBucket; i++ )
    {
        Bucket[ i ] = Create( );
    }

    /* First Sort  */
    for( i = 0; i < Size; i++ )
    {
        Tmp = Bucket[ Numeric[ i ] % NBucket ]; 
        Insert( Numeric[ i ], Last( Tmp ), Tmp );
    }
    /* Print bucket  */
    printf( "First: \n" );
    PrintArr( Bucket, NBucket );

    for( j = NBucket; --Count > 0; j *= NBucket )
    {
        for( i = 0; i < NBucket; i++ )
        {
            Tmp = Create( );
            while( !IsEmpty( Bucket[ i ] ) )
            {
                Num = First( Bucket[ i ] )->Element;
                Insert( Num, Last( Tmp ), Tmp );
                Delete( Num, Bucket[ i ] );
            }
            P = Tmp->Next;
            while( P != NULL )
            {
                Num = ( P->Element / j ) % NBucket;
                Insert( P->Element, Last( Bucket[ Num ] ), Bucket[ Num ] );
                P = P->Next;
            }
        }
        printf( "Bucket: \n" );
        PrintArr( Bucket, NBucket );
    }
    DeleteList( Tmp );
}

/* Radix Sort  */
void Radix( int Numeric[ ], int Size )
{
    int i, j, Num;
    List Tmp;
    Position P;

    List Bucket[ 10 ];

    for ( i = 0; i < 10; i++ )
    {
        Bucket[ i ] = Create( );
    }

    for( i = 0; i < Size; i++ )
    {
        Tmp = Bucket[ Numeric[ i ] % 10 ];
        Insert( Numeric[ i ], Last( Tmp ), Tmp );
    }
    printf( "First:\n" );
    PrintArr( Bucket, Size );

    for( j = 10; j <= 100; j *= 10 ){
        for ( i = 0; i < 10; i++ )
        {
            Tmp = Create( );
            while( !IsEmpty( Bucket[ i ] ) )
            {
                Num = First( Bucket[ i ] )->Element;
                Insert( Num, Last( Tmp ), Tmp );
                Delete( Num, Bucket[ i ] );
            }
            P = Tmp->Next;
            while( P != NULL )
            {
                Num = ( P->Element / j ) % 10;
                Insert( P->Element, Last( Bucket[ Num ] ), Bucket[ Num ] );
                P = P->Next;
            }
        }
        printf( "Bucket: \n" );
        PrintArr( Bucket, Size );
    }

    DeleteList( Tmp );
}
