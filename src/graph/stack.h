#ifndef _Stack_h_
#define _Stack_h_

#include "types.h"

typedef struct Node *PtrToNode;
struct Node {
	ElementType Element;
	PtrToNode   Next;
};

typedef PtrToNode Stack;

int StackIsEmpty( Stack S );
Stack CreateStack( void );
void DisposeStack( Stack S );
//void MakeEmpty( Stack S );
void Push(ElementType X, Stack S );
ElementType Top( Stack S );
ElementType Pop( Stack S );

#endif  /* _Stack_h */

