#include "stack.h"
#include <stdlib.h>

static void MakeEmpty( Stack S );

int StackIsEmpty( Stack S )
{
	return S->Next == NULL;
}

Stack CreateStack( void )
{
	Stack S;

	if (!(S = malloc(sizeof(struct Node))))
		return NULL;

	S->Next = NULL;
	MakeEmpty( S );

	return S;
}

void MakeEmpty( Stack S )
{
	if (S == NULL)
		return;

	while( !StackIsEmpty( S ) )
		Pop( S );

	return;
}

void DisposeStack( Stack S )
{
	MakeEmpty( S );
	free( S );
}

void Push( ElementType X, Stack S )
{
	PtrToNode TmpCell;

	if (!(TmpCell = malloc(sizeof(struct Node))))
		return;

	TmpCell->Element = X;
	TmpCell->Next = S->Next;
	S->Next = TmpCell;

	return;
}

ElementType Top( Stack S )
{
	if (!StackIsEmpty( S ) )
		return S->Next->Element;

	return 0;
}

ElementType Pop( Stack S )
{
	PtrToNode FirstCell;
	ElementType e;

	if (StackIsEmpty(S))
		return 0;

	FirstCell = S->Next;
	S->Next = S->Next->Next;
	e = FirstCell->Element;
	free(FirstCell);

	return e; 
}
