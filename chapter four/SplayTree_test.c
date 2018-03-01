#include "SplayTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../times.h"

/* This is a test function to test Splay Tree  */
int main( int argc, char *argv[ ] )
{
    SplayTree T;
    int num, i, insert_times, find_times;
    time_t t;

    if( argc <= 1 )
    {
        printf( "Usgae: Tree_test -insert_times -find_times\n" );
        return 1;
    }

    insert_times = atoi( argv[ 1 ] + 1 );
    find_times   = atoi( argv[ 2 ] + 1 );

    printf( "insert_times: %d\n", insert_times );
    printf( "insert_times: %d\n", find_times );
    

    T = Create( );
    srand( ( unsigned int )time( NULL ) );

    /* Start  */
    sstart( );

    /* n times inserts  */
    for( i = 0; i < insert_times; i++ )
    {
        num = rand( ) % 1000;
        Insert( num, T );
    }

    /* n times finds  */
    for( i = 0; i < find_times; i++ )
    {
        num = rand( ) % 1000;
        Find( num, T );
    }

    /* Stop  */
    t = sstop( );
    printf( "Total: %lu\n", t );

    return 0;
}


