#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

struct Node
{
	ElementType Element;
	PtrToNode   Next;
};

int IsEmpty( Stack S )
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

	while( !IsEmpty( S ) )
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
	if (!IsEmpty( S ) )
		return S->Next->Element;

	return NULL;
}

ElementType Pop( Stack S )
{
	PtrToNode FirstCell;
	ElementType e;

	if (IsEmpty(S))
		return NULL;

	FirstCell = S->Next;
	S->Next = S->Next->Next;
	e = FirstCell->Element;
	free(FirstCell);

	return e; 
}

/*
int main(void)
{
	Stack S;
	ElementType X;

	S = CreateStack();
	Push("World", S);
	Push("Hello", S);

	while ((X = Pop(S)))
		printf("%s ", (char *)X);
	printf("\n");

	return 0;
}
*/
