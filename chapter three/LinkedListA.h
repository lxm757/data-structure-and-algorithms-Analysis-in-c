#ifndef _Cursor_H

typedef int ElementType;
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

void InitializeCursorSpace( void );

List Create( void );
List MakeEmpty( List L ); /* Imp  */
int IsEmpty( const List L );  /* Imp  */
int IsLast( const Position P, const List L ); /* Imp  */
Position Find( ElementType X, const List L ); /* Imp  */
Position Finds( ElementType X, const List L ); /* Imp  */
void Delete( ElementType X, const List L ); /* Imp  */
Position FindPrevious( ElementType X, const List L ); /* Imp  */
void Insert( ElementType X, Position P, List L ); /* Imp  */
void DeleteList( List L ); /* Imp  */
Position Header( const List L ); /* Imp  */
Position First( const List L ); /* Imp  */
Position Last( const List L );
Position Advance( const Position P );
ElementType Retrieve( const Position P );
void Print( const List L ); /* Imp  */

#endif
