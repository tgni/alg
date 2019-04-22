#include "binheap.h"
#include "fatal.h"
#include <stdlib.h>

#define MinPQSize (10)
#define MinData (-32767)

static void Ecpy(HeapElemType *d, HeapElemType *s)
{
        d->v = s->v;
        d->dv = s->dv;
}

/*big >= small , return 1; else return 0*/
static int Ecmp(HeapElemType *b, HeapElemType *s)
{
        if (b->dv >= s->dv)
                return 1;
        else 
                return 0;
}

static void MakeEmpty( PriorityQueue H )
{
        H->Size = 0;
}

static int IsEmpty( PriorityQueue H )
{
        return H->Size == 0;
}

static int IsFull( PriorityQueue H )
{
        return H->Size == H->Capacity;
}

/* H->Element[ 0 ] is a sentinel */

static void Insert( HeapElemType X, PriorityQueue H )
{
        int i;

        if( IsFull( H ) )
        {
                Error( "Priority queue is full" );
                return;
        }

        for( i = ++H->Size; Ecmp(&H->Elements[ i / 2 ], &X); i /= 2 )
        {
                Ecpy(&H->Elements[ i ], &H->Elements[ i / 2 ]);
        }
        Ecpy(&H->Elements[ i ], &X);
}

static HeapElemType DeleteMin( PriorityQueue H )
{
        int i, Child;
        HeapElemType MinElement, LastElement;

        if( IsEmpty( H ) )
        {
                Error( "Priority queue is empty" );
                return H->Elements[ 0 ];
        }
        Ecpy(&MinElement, &H->Elements[ 1 ]);
        Ecpy(&LastElement, &H->Elements[ H->Size-- ]);

        for( i = 1; i * 2 <= H->Size; i = Child )
        {
                /* Find smaller child */
                Child = i * 2;
                if( Child != H->Size 
                        && Ecmp(&H->Elements[ Child ], &H->Elements[ Child + 1]) )
                        Child++;

                /* Percolate one level */
                if ( Ecmp(&LastElement, &H->Elements[ Child ]) )
                        Ecpy(&H->Elements[ i ], &H->Elements[ Child ]);
                else
                        break;
        }
        Ecpy(&H->Elements[ i ], &LastElement);
        return MinElement;
}

static HeapElemType FindMin( PriorityQueue H )
{
        if( !IsEmpty( H ) )
                return H->Elements[ 1 ];
        Error( "Priority Queue is Empty" );
        return H->Elements[ 0 ];
}

void Destroy( PriorityQueue H )
{
        free( H->Elements );
        free( H );
}


PriorityQueue Initialize( int MaxElements )
{
        PriorityQueue H;

        if( MaxElements < MinPQSize )
                Error( "Priority queue size is too small" );

        H = malloc( sizeof( struct HeapStruct ) );
        if( H ==NULL )
                FatalError( "Out of space!!!" );

        /* Allocate the array plus one extra for sentinel */
        H->Elements = malloc( ( MaxElements + 1 )
                * sizeof( HeapElemType ) );
        if( H->Elements == NULL )
                FatalError( "Out of space!!!" );

        H->Capacity = MaxElements;
        H->Size = 0;
        H->Elements[ 0 ].dv = MinData;
        H->Elements[ 0 ].v = 0;

        H->MakeEmpty = MakeEmpty;
        H->Insert = Insert;
        H->DeleteMin = DeleteMin;
        H->FindMin = FindMin;
        H->IsEmpty = IsEmpty;
        H->IsFull = IsFull;

        return H;
}
