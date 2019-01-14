#ifndef _Queue_h
#define _Queue_h

#include "types.h"

typedef struct QueueRecord *Queue;

struct QueueRecord {
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType *Array;
	
	int (*IsFull)( Queue Q );
	void (*Enqueue)( ElementType X, Queue Q );
	ElementType (*Dequeue)( Queue Q );
	int (*IsEmpty)( Queue Q );
};

Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);

#endif  /* _Queue_h */
/* END */
