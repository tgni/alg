#include "tree.h"
#include <stdlib.h>
#include "fatal.h"

SearchTree MakeEmpty( SearchTree T )
{
	/* This version can't avoid if T is NULL when first Input T. */
#if 0
	if (T->Left)
		T->Left = MakeEmpty(T->Left);
	if (T->Right)
		T->Right = MakeEmpty(T->Right);
	free(T);
	return NULL;
#endif
	if (T) {
		MakeEmpty(T->Left);	
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;

}

Position Find( ElementType X, SearchTree T )
{
	/* first we use loop version */
#if 0
	while (T) {
		if (X > T->Element)	
			T = T->Right;
		else if (X < T->Element)
			T = T->Left;
		else
			return T;
	}
	return NULL;
#endif
	/* second we use recursive version */
	if (T) {
		if (X > T->Element)	
			return Find(X, T->Right);
		else if (X < T->Element)
			return Find(X, T->Left);
		else
			return T;
	}

	return NULL;
}

Position FindMin( SearchTree T )
{
	if (!T)
		return NULL;
	if (!T->Left)
		return T;
	else
		return FindMin(T->Left);
}

Position FindMax( SearchTree T )
{
	if (!T)
		return NULL;
	if (!T->Right)
		return T;
	else
		return FindMax(T->Right);
}

SearchTree Insert( ElementType X, SearchTree T )
{
	if (T == NULL) {
		if (!(T = (SearchTree)malloc(sizeof(struct TreeNode)))) {
			FatalError("Out of Memory!");
		} else {
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	} else if (X < T->Element) {
		T->Left  = Insert(X, T->Left);
	} else if (X > T->Element) {
		T->Right = Insert(X, T->Right);
	} else {
		/* T is already done, do nothing */
	}

	return T;
}

SearchTree Delete( ElementType X, SearchTree T )
{
	Position TmpCell;

	if (T == NULL)
		Error("Element not found");
	else if (X < T->Element)
		/* return value to update left subtree */
		T->Left = Delete(X, T->Left);
	else if (X > T->Element)
		T->Right = Delete(X, T->Right);
	else if (T->Left && T->Right) {
		/* we only substitue value of Target Position, 
		 * and remove TmpCell from Right subtree 
		 */ 
		TmpCell = FindMin(T->Right);	
		T->Element = TmpCell->Element;
		T->Right = Delete(T->Element, T->Right);
	} else {  /* One or zero Children */
		TmpCell = T;
		if (T->Left == NULL)	/* handle One Right or None Children */
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}

	return T;
}

ElementType Retrieve( Position P )
{
	return P->Element;
}
