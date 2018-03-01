#include "SearchTree.h"
#include "../times.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* This is a test function for SearchTree  */
/* Usgae: Tree_test -insert_times -find_times  */
int main( int argc, char *argv[ ] )
{

    int i, num, insert_times, find_times;
    time_t t;

    SearchTree T;

    if( argc <= 1 )
    {
        printf( "Usage: Tree_test -Insert_times -Find_times\n" );
        return 1;
    }

    insert_times = atoi( argv[ 1 ] + 1 );
    find_times   = atoi( argv[ 2 ] + 1 );

    printf( "insert_times: %d\n", insert_times );
    printf( "find_fimes  : %d\n", find_times );

    /* Initialized  */
    srand( ( unsigned int )time( NULL ) );
    T = Create( );

    /* Start  */
    sstart( );

    /* insert_times times inserts  */
    for( i = 0; i < insert_times; i++ )
    {
        num = rand( ) % 1000;
        Insert( num, T );
    }

    /* find_times times Find  */
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
