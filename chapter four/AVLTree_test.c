#include "AVLTree.h"
#include "../times.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* This is a test for AVL Tree  */
int main( int argc, char *argv[ ] )
{
    int i, num, insert_times, find_times;
    time_t t;
    AvlTree T;

    if( argc <= 1 )
    {
        printf( "Usage: Tree_test -insert_times -find_times\n" );
        return 1;
    }

    insert_times = atoi( argv[ 1 ] + 1 );
    find_times   = atoi( argv[ 2 ] + 1 );

    printf( "insert_times: %d\n", insert_times );
    printf( "find_times  : %d\n", find_times );

    /* Initialized  */
    srand( ( unsigned int )time( NULL ) );
    T = Create( );
    
    /* Start  */
    sstart( );
    
    /* n times inserts  */
    for( i = 0; i < insert_times; i++ )
    {
        num = rand() % 1000;
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

