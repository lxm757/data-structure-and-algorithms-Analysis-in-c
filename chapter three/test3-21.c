#include <stdio.h>
/* Two stack use one array  */

#define SpaceSize 10

int CursorSpace[ SpaceSize ];

struct Node 
{
    int Position;
} StackTop, StackBot;

/* Initialize  */
void Initialize( void )
{
    StackTop.Position = 0;
    StackBot.Position = SpaceSize;
}

/* Is empty  */
int IsStackTopEmpty( void )
{
    return StackTop.Position <= 0;
}

int IsStackBotEmpty( void )
{
    return StackBot.Position >= SpaceSize;
}

/* Push  */
void PushStackTop( int Element )
{
    if( StackTop.Position >= StackBot.Position )
    {
        printf( "%-3d:%3d\n", StackTop.Position, 
                StackBot.Position );
        printf( "Stack Full\n" );
    }
    else 
    {
        CursorSpace[ StackTop.Position++ ] = Element;
    }
}

void PushStackBot( int Element )
{
    if( StackBot.Position - 1 < StackTop.Position )
    {
        printf( "%-3d:%3d\n", StackTop.Position, 
               StackBot.Position ); 
        printf( "Stack Full\n" );
    }
    else 
    {
        CursorSpace[ --StackBot.Position ] = Element;
    }
}

/* Pop  */
int PopStackTop( void )
{
    if( IsStackTopEmpty( ) )
    {
        printf( "StackTop Empty\n" );
        return 0; /* This 0 used to avoid warning  */
    }
    return CursorSpace[ --StackTop.Position ];
}

int PopStackBot( void )
{
    if( IsStackBotEmpty( ) )
    {
        printf( "StackBot Empty\n" );
        return 0; /* This 0 used to avoid warning  */
    }
    return CursorSpace[ StackBot.Position++ ];
}

/* Make empty  */
void MakeStackTopEmpty( void )
{
    while( !IsStackTopEmpty( ) )
    {
        PopStackTop( );
    }
}

void MakeStackBotEmpty( void )
{
    while( !IsStackBotEmpty( ) )
    {
        PopStackBot( );
    }
}

/* Test  */
int main( void )
{
    Initialize( );

    int i;
    for( i = 1; i < SpaceSize / 2; i++ )
    {
        PushStackTop( i );
    }
    
    for( i = SpaceSize; i >= SpaceSize / 2 ; i-- )
    {
        PushStackBot( i );
    }

    for( i = 0; i < SpaceSize; i++ )
    {
        printf( "%d\n", CursorSpace[ i ] );
    }

    return 0;
}
