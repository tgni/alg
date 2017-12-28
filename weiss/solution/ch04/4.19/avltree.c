#include "avltree.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fatal.h"
#include "que.h"
#include "stack.h"

#define DIST_MAX	(100)

typedef struct AvlNode
{
	list_head_t	List;

	int		Height;
	int		Dist;
	int		Depth;

	ElementType	Element;
	AvlTree		Left;
	AvlTree		Right;
} AvlNode_t;

AvlTree MakeEmpty( AvlTree T )
{
	if( T != NULL )
	{
		MakeEmpty( T->Left );
		MakeEmpty( T->Right );
		free( T );
	}
	return NULL;
}

Position Find( ElementType X, AvlTree T )
{
	if( T == NULL )
		return NULL;
	if( X < T->Element )
		return Find( X, T->Left );
	else
		if( X > T->Element )
			return Find( X, T->Right );
		else
			return T;
}

Position FindMin( AvlTree T )
{
	if( T == NULL )
		return NULL;
	else
		if( T->Left == NULL )
			return T;
		else
			return FindMin( T->Left );
}

Position FindMax( AvlTree T )
{
	if( T != NULL )
		while( T->Right != NULL )
			T = T->Right;

	return T;
}

static int Height( Position P )
{
	if( P == NULL )
		return -1;
	else
		return P->Height;
}

static int Max( int Lhs, int Rhs )
{
	return Lhs > Rhs ? Lhs : Rhs;
}

/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */
/*		K2		 K1		 	
 *	       /  \		/  \
 *	      K1   Z    =>     X   K2
 *	     /  \                 /  \
 *	    X    Y               Y    Z
 */
static Position SingleRotateWithLeft( Position K2 )
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;

	K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
	K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

	return K1;  /* New root */
}

/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */
/*		K1		 K2		 	
 *	       /  \		/  \
 *	      X   K2    =>     K1   Z
 *	         /  \         /  \
 *	        Y    Z       X    Y
 */
static Position SingleRotateWithRight( Position K1 )
{
	Position K2;

	K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;

	K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
	K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

	return K2;  /* New root */
}

/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */
/*		K3		     K3                     K2
 *	       /  \		    /  \                   /  \
 *	      K1   D		   K2   D                K1    K3
 *	     /  \	  =>      /  \        =>        / \   /  \
 *	    A    K2		 K1   C		       A   B C    D
 *	        /  \		/  \
 *	       B    C          A    B
 */
static Position DoubleRotateWithLeft( Position K3 )
{
	/* Rotate between K1 and K2 */
	K3->Left = SingleRotateWithRight( K3->Left );

	/* Rotate between K3 and K2 */
	return SingleRotateWithLeft( K3 );
}

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */
/*		K1		      K1                     K2
 *	       /  \		     /  \                   /  \
 *	      A    K3		    A   K2                K1    K3
 *	          /  \	  =>           /  \       =>     / \   /  \
 *	         K2   D		      B   K3		A   B C    D
 *	        /  \			 /  \
 *	       B    C			C    D
 */
static Position DoubleRotateWithRight( Position K1 )
{
	/* Rotate between K3 and K2 */
	K1->Right = SingleRotateWithLeft( K1->Right );

	/* Rotate between K1 and K2 */
	return SingleRotateWithRight( K1 );
}


AvlTree Insert( ElementType X, AvlTree T )
{
	if( T == NULL )
	{
		/* Create and return a one-node tree */
		T = malloc( sizeof( struct AvlNode ) );
		if( T == NULL )
			FatalError( "Out of space!!!" );
		else
		{
			T->Element = X; T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else
	{
		if( X < T->Element )
		{
			T->Left = Insert( X, T->Left );
			if( Height( T->Left ) - Height( T->Right ) == 2 )
				if( X < T->Left->Element )
					T = SingleRotateWithLeft( T );
				else
					T = DoubleRotateWithLeft( T );
		}
		else 
		{
			if( X > T->Element )
			{
				T->Right = Insert( X, T->Right );
				if( Height( T->Right ) - Height( T->Left ) == 2 )
					if( X > T->Right->Element )
						T = SingleRotateWithRight( T );
					else
						T = DoubleRotateWithRight( T );
			}
		}
	}

	/* Else X is in the tree already; we'll do nothing */
	T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
	return T;
}

AvlTree CreateNewNode(ElementType X)
{
	AvlTree T;

	if (!(T = malloc(sizeof(struct AvlNode)))) {
		FatalError("Out of space!!!");
	} else {
		T->Element = X; T->Height = 0;
		T->Left = T->Right = NULL;
	}

	return T;
}

/* This Loop Version Insert isn't faster than Recursive Version Insert,
 * For test 10,000,000 data insertion, Recursive version used 17s, while
 * Loop version used 25s! 
 */
AvlTree LoopInsert(ElementType X, AvlTree T)
{
	stack_t S;
	AvlTree P, Q;
	int IsRotate = FALSE;
	
	stack_init(&S, "insertion path stack", offset_of(AvlNode_t, List));

	while (T) {
		if (X < T->Element) {
			push(&S, T);
			T = T->Left;
		} else if (X > T->Element) {
			push(&S, T);
			T = T->Right;
		} else {
			break;
		}
	}

	if (T == NULL) {
		if (!(T = malloc(sizeof(struct AvlNode)))) {
			FatalError("Out of space!!!");
			return NULL;
		}

		T->Element = X; T->Height = 0;
		T->Left = T->Right = NULL;
		if ((Q = pop(&S))) {
			if (T->Element < Q->Element)
				Q->Left = T;
			else
				Q->Right = T;
			push(&S, Q);
		}
		push(&S, T);
	}

	while ((T = pop(&S))) {
		T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
		if (X < T->Element) {
			if (Height(T->Left) - Height(T->Right) == 2) {
				if (X < T->Left->Element)
					T = SingleRotateWithLeft(T);
				else
					T = DoubleRotateWithLeft(T);
				IsRotate = TRUE;
			}
		} else if (X > T->Element) {
			if (Height(T->Right) - Height(T->Left) == 2) {
				if(X > T->Right->Element)
					T = SingleRotateWithRight(T);
				else
					T = DoubleRotateWithRight(T);
				IsRotate = TRUE;
			}
		}
		if (IsRotate == TRUE) {
			IsRotate = FALSE;
			if ((Q = pop(&S))) {
				if (T->Element < Q->Element)
					Q->Left = T;
				else
					Q->Right = T;
				push(&S, Q);
			}
		}
		P = T;
	}

	return P;
}


void ComputeDistAndDepth( AvlTree T )
{
	que_t que;
	int Depth, Dist;

	if (T == NULL)
		return;

	que_init(&que, "avltree que", offset_of(AvlNode_t, List));

	T->Dist  = DIST_MAX;
	T->Depth = 0;
	enqueue(&que, T);

	while ((T = dequeue(&que))) {
		if (T->Left) {
			T->Left->Depth = T->Depth + 1;
			T->Left->Dist  = T->Dist - round(DIST_MAX/pow(2, T->Left->Depth));
			enqueue(&que, T->Left);	
		}
		if (T->Right) {
			T->Right->Depth = T->Depth + 1;
			T->Right->Dist  = T->Dist + round(DIST_MAX/pow(2, T->Right->Depth));
			enqueue(&que, T->Right);
		}
	}
}


AvlTree Delete( ElementType X, AvlTree T )
{
	Position TmpCell;	

	if (T == NULL) {
		Error("Element not found");
		return T;
	}

	if (X < T->Element) {
		T->Left = Delete(X, T->Left);
		if (Height(T->Right) - Height(T->Left) == 2) {
			if (Height(T->Right->Right) > Height(T->Right->Left))
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	} else if (X > T->Element) {
		T->Right = Delete(X, T->Right);
		if (Height(T->Left) - Height(T->Right) == 2) {
			if (Height(T->Left->Left) > Height(T->Left->Right))
				T = SingleRotateWithLeft(T); 
			else
				T = DoubleRotateWithLeft(T);
		}
	} else if (T->Left && T->Right) {
		TmpCell = FindMin(T->Right);
		T->Element = TmpCell->Element;
		T->Right = Delete(T->Element, T->Right);
		if (Height(T->Left) - Height(T->Right) == 2) {
			if (Height(T->Left->Left) > Height(T->Left->Right))
				T = SingleRotateWithLeft(T); 
			else
				T = DoubleRotateWithLeft(T);
		}
	} else {
		TmpCell = T;
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}

	if (T)
		T->Height = Max(Height(T->Left), Height(T->Right)) + 1;

	return T;
}

ElementType Retrieve( Position P )
{
	return P->Element;
}


#define NR_DEPTH_MAX	256
static int __LAST[NR_DEPTH_MAX]; 

void list_dir(AvlTree T)
{
	int i;

	for (i = 0; i < T->Depth; ++i) {
		if (i == T->Depth - 1)
			printf("%s", __LAST[i] ? "`-- " : "|-- ");
		else
			printf("%s", __LAST[i] ? "    " : "|   ");
	}
	printf("%d\n", T->Element);

	if (!T->Left && !T->Right) {
		return;
	} else if (T->Left && !T->Right) {
		__LAST[T->Depth] = 1;
		list_dir(T->Left);
	} else if (!T->Left && T->Right) {
		__LAST[T->Depth] = 1;
		list_dir(T->Right);
	} else {
		__LAST[T->Depth] = 0;
		list_dir(T->Left);
		__LAST[T->Depth] = 1;
		list_dir(T->Right);
	}
}

void VPrintAvlTree(AvlTree T)
{
	if (T)
		list_dir(T);
}

static int32_t DEPTH = 0;
static int32_t DIST  = 0;
static int32_t WIDTH = 0;
static char BUF[1024] = {0};
static int32_t BUF_POS = 0;

static inline int32_t ComputeWidth(int32_t X)
{
	int32_t width = 0;

	if (X < 0) {
		X = -X;
		++width;
	}
	do {
		++width;
	} while ((X /= 10) > 0);

	return width;
}

void PrintNode(AvlTree T)
{
	int32_t i;

	if (T->Depth != DEPTH) {
		printf("\n");
		DIST = T->Dist;
		BUF[BUF_POS++] = '\n';
		BUF[BUF_POS]   = '\0';
		printf("%s", BUF);
		//memset(BUF, 0, sizeof(BUF));
		BUF_POS = 0;
	} else {
		DIST = T->Dist - DIST - WIDTH;
	}

	for (i = 0; i < DIST; ++i)
		printf(" ");
	printf("%d", T->Element);

	DIST  = T->Dist;
	DEPTH = T->Depth;
	WIDTH = ComputeWidth(T->Element);

	if (T->Left && !T->Right) {
		for ( ; BUF_POS < T->Left->Dist; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '/';
		for ( ; BUF_POS < T->Dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '|';
	} else if (!T->Left && T->Right) {
		for ( ; BUF_POS < T->Dist; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '|';
		for ( ; BUF_POS < T->Right->Dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '\\';
	} else if (T->Left && T->Right) {
		for ( ; BUF_POS < T->Left->Dist; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '/';
		for ( ; BUF_POS < T->Dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '|';
		for ( ; BUF_POS < T->Right->Dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '\\';
	}

	return;
}

void HPrintAvlTree(AvlTree T)
{
	que_t que;

	if (T == NULL)
		return;

	que_init(&que, "avltree que", offset_of(AvlNode_t, List));
	enqueue(&que, T);

	while ((T = dequeue(&que))) {
		PrintNode(T);
		if (T->Left)
			enqueue(&que, T->Left);
		if (T->Right)
			enqueue(&que, T->Right);
	}

	printf("\n");

	return;
}
