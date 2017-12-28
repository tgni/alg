        #include "queue.h"
        #include "fatal.h"
        #include <stdlib.h>

        #define MinQueueSize ( 5 )

        struct QueueRecord
        {
            int Capacity;
            int Front;
            int Rear;
            int Size;
            ElementType *Array;
        };

        static int IsEmpty( Queue Q );
        static int IsFull( Queue Q );
        static void MakeEmpty( Queue Q );
        static void Enqueue( ElementType X, Queue Q );
        static ElementType Front( Queue Q );
        static void Dequeue( Queue Q );
        static ElementType FrontAndDequeue( Queue Q );

/* START: fig3_58.txt */
        static int
        IsEmpty( Queue Q )
        {
            return Q->Size == 0;
        }
/* END */

        static int
        IsFull( Queue Q )
        {
            return Q->Size == Q->Capacity;
        }

        Queue
        CreateQueue( int MaxElements )
        {
            Queue Q;

/* 1*/      if( MaxElements < MinQueueSize )
/* 2*/          Error( "Queue size is too small" );

/* 3*/      Q = malloc( sizeof( struct QueueRecord ) );
/* 4*/      if( Q == NULL )
/* 5*/          FatalError( "Out of space!!!" );

/* 6*/      Q->Array = malloc( sizeof( ElementType ) * MaxElements );
/* 7*/      if( Q->Array == NULL )
/* 8*/          FatalError( "Out of space!!!" );
/* 9*/      Q->Capacity = MaxElements;
/*10*/      MakeEmpty( Q );

/*11*/      return Q;
        }

/* START: fig3_59.txt */
        static void
        MakeEmpty( Queue Q )
        {
            Q->Size = 0;
            Q->Front = 1;
            Q->Rear = 0;
        }
/* END */

        void
        DisposeQueue( Queue Q )
        {
            if( Q != NULL )
            {
                free( Q->Array );
                free( Q );
            }
        }

/* START: fig3_60.txt */

        static int
        Succ( int Value, Queue Q )
        {
            if( ++Value == Q->Capacity )
                Value = 0;
            return Value;
        }

        static void
        Enqueue( ElementType X, Queue Q )
        {
            if( IsFull( Q ) )
                Error( "Full queue" );
            else
            {
                Q->Size++;
                Q->Rear = Succ( Q->Rear, Q );
                Q->Array[ Q->Rear ] = X;
            }
        }
/* END */



        static ElementType
        Front( Queue Q )
        {
            if( !IsEmpty( Q ) )
                return Q->Array[ Q->Front ];
            Error( "Empty queue" );
            return 0;  /* Return value used to avoid warning */
        }

        static void
        Dequeue( Queue Q )
        {
            if( IsEmpty( Q ) )
                Error( "Empty queue" );
            else
            {
                Q->Size--;
                Q->Front = Succ( Q->Front, Q );
            }
        }

        static ElementType
        FrontAndDequeue( Queue Q )
        {
            ElementType X = 0;

            if( IsEmpty( Q ) )
                Error( "Empty queue" );
            else
            {
                Q->Size--;
                X = Q->Array[ Q->Front ];
                Q->Front = Succ( Q->Front, Q );
            }
            return X;
        }

struct QueueOps *RegisterQueueOps(void)
{
        struct QueueOps *op;
        
        op = (struct QueueOps *)malloc(sizeof(struct QueueOps));
        if (!op)  return NULL;

        op->IsEmpty = IsEmpty;
        op->IsFull = IsFull;
        op->MakeEmpty = MakeEmpty;
        op->Enqueue = Enqueue;
        op->Front = Front;
        op->Dequeue = Dequeue;
        op->FrontAndDequeue = FrontAndDequeue;

        return op;
}

void UnRegisterQueueOps(struct QueueOps *op)
{
        if (op) free(op);
}
