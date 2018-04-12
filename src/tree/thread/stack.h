#ifndef _Stack_h_
#define _Stack_h_

#include "types.h"

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef void * ElementType;

int IsEmpty( Stack S );
Stack CreateStack( void );
void DisposeStack( Stack S );
void MakeEmpty( Stack S );
void Push(ElementType X, Stack S );
ElementType Top( Stack S );
ElementType Pop( Stack S );

#endif  /* _Stack_h */

