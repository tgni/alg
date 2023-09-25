#ifndef _BinHeap_H
#define _BinHeap_H

typedef struct element_type_s {
	char c;
	int p;
	int v;	/* edge value */
	struct element_type_s *parent, *left, *right; 
} ElementType;

struct HeapStruct {
	int Capacity;
	int Size;
	ElementType **Elements;
};

typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize( int MaxElements );
void Destroy( PriorityQueue H );
void MakeEmpty( PriorityQueue H );
void Insert( ElementType *X, PriorityQueue H );
ElementType * DeleteMin( PriorityQueue H );
ElementType * FindMin( PriorityQueue H );
int IsEmpty( PriorityQueue H );
int IsFull( PriorityQueue H );

#endif
