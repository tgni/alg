#ifndef _Queue_h
#define _Queue_h

typedef void * ElementType;
struct QueueRecord;
typedef struct QueueRecord *Queue;

int IsFull( Queue Q );
Queue CreateQueue( int MaxElements );
void DisposeQueue( Queue Q );
void Enqueue( ElementType X, Queue Q );
ElementType Front( Queue Q );
ElementType Dequeue( Queue Q );
int IsEmptyQ( Queue Q );

#endif  /* _Queue_h */
/* END */
