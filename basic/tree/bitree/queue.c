#include "queue.h"
#include "fatal.h"
#include <stdlib.h>

#define MinQueueSize ( 5 )

struct QueueRecord {
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType *Array;
};

static void MakeEmpty( Queue Q );

int IsEmptyQ( Queue Q )
{
	return Q->Size == 0;
}

int IsFull( Queue Q )
{
	return Q->Size == Q->Capacity;
}

Queue CreateQueue( int MaxElements )
{
	Queue Q;

	if( MaxElements < MinQueueSize )
		Error( "Queue size is too small" );

	Q = malloc( sizeof( struct QueueRecord ) );
	if( Q == NULL )
		FatalError( "Out of space!!!" );

	Q->Array = malloc( sizeof( ElementType ) * MaxElements );
	if( Q->Array == NULL )
		FatalError( "Out of space!!!" );
	Q->Capacity = MaxElements;
	MakeEmpty( Q );

	return Q;
}

void MakeEmpty( Queue Q )
{
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}

void DisposeQueue( Queue Q )
{
	if( Q != NULL ) {
		free( Q->Array );
		free( Q );
	}
}

static int Succ( int Value, Queue Q )
{
	if( ++Value == Q->Capacity )
		Value = 0;
	return Value;
}

void Enqueue( ElementType X, Queue Q )
{
	if( IsFull( Q ) )
		Error( "Full queue" );
	else {
		Q->Size++;
		Q->Rear = Succ( Q->Rear, Q );
		Q->Array[ Q->Rear ] = X;
	}
}

ElementType Front( Queue Q )
{
	if( !IsEmptyQ( Q ) )
		return Q->Array[ Q->Front ];
	Error( "Empty queue" );
	return 0;
}

/*
void Dequeue( Queue Q )
{
	if ( IsEmptyQ( Q ) )
		Error( "Empty queue" );
	else {
		Q->Size--;
		Q->Front = Succ( Q->Front, Q );
	}
}
*/

ElementType Dequeue( Queue Q )
{
	ElementType X = 0;

	if( IsEmptyQ( Q ) ) {
		return (ElementType)0;
	} else {
		Q->Size--;
		X = Q->Array[ Q->Front ];
		Q->Front = Succ( Q->Front, Q );
	}
	return X;
}
