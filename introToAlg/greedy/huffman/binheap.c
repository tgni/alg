#include "binheap.h"
#include "fatal.h"
#include <stdlib.h>

#define MinData (-32767)

ElementType Sentinel = {
	' ', MinData, 0, NULL, NULL, NULL,
};

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	int i;

	if (!(H = malloc(sizeof(struct HeapStruct))))
		FatalError("Out of space!!!");

	/* Allocate the array plus one extra for sentinel */
	if (!(H->Elements = malloc((MaxElements + 1) * sizeof(ElementType *))))
		FatalError("Out of space!!!");

	H->Capacity = MaxElements;
	H->Size = 0;

	for (i = 0; i < MaxElements + 1; ++i)
		H->Elements[i] = NULL;

	H->Elements[0] = &Sentinel;

	return H;
}

void MakeEmpty(PriorityQueue H)
{
	H->Size = 0;
}

/* H->Element[0] is a sentinel */

int ElementCmp(ElementType *x, ElementType *y)
{
	if (x->p < y->p)
		return -1;

	return x->p > y->p;
}

void Insert(ElementType *X, PriorityQueue H)
{
	int i;

	if (IsFull(H)) {
		Error("Priority queue is full");
		return;
	}

	for (i = ++H->Size; ElementCmp(H->Elements[i/2], X) >= 0; i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = X;
}

ElementType * DeleteMin(PriorityQueue H)
{
	int i, Child;
	ElementType *MinElement, *LastElement;

	if (IsEmpty(H)) {
		Error("Priority queue is empty");
		return H->Elements[0];
	}
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for(i = 1; i * 2 <= H->Size; i = Child)
	{
		/* Find smaller child */
		Child = i * 2;
		//if(Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
		if (Child != H->Size && ElementCmp(H->Elements[Child+1], H->Elements[Child]) < 0)
			Child++;

		/* Percolate one level */
		//if(LastElement > H->Elements[Child])
		if(ElementCmp(LastElement, H->Elements[Child]) >= 0)
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}

ElementType * FindMin(PriorityQueue H)
{
	if(!IsEmpty(H))
		return H->Elements[1];
	Error("Priority Queue is Empty");
	return H->Elements[0];
}

int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}

void Destroy(PriorityQueue H)
{
	free(H->Elements);
	free(H);
}
