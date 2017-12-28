#include <stdio.h>
#include "list.h"

#define NELEMS(array)	(sizeof(array) / sizeof(array[0]))

void PrintList(List L)
{
	Position p;

	for (p = First(L); p ; p = Advance(p)) {
		printf("%d ", Retrieve(p));	
	}
	printf("\n");
}

void ListAddTail(ElementType X, List L)
{
	Position p;

	if ((p = FindPrevious(X, L)))
		Insert(X, L, p);
	else
		Insert(X, L, L);
}

List InitList(ElementType A[], int N)
{
	List L;
	int i;

	L = MakeEmpty(NULL);
	for (i = 0; i < N; ++i) {
		ListAddTail(A[i], L);	
	}
	return L;
}

List copy(List A)
{
	Position p;
	List L;

	L = MakeEmpty(NULL);
	for (p = First(A); p ; p = Advance(p)) {
		ListAddTail(Retrieve(p), L);	
	}
	return L;
}

List and(List A, List B)
{
	List C;
	ElementType e;
	Position p, q, r;
	
	C = MakeEmpty(NULL);
	for (p = First(A); p ; p = Advance(p)) {
		e = Retrieve(p);
		for (q = First(B); q; q = Advance(q)) {
			if (e == Retrieve(q)) {
				ListAddTail(e, C);
				continue;
			}
		}
	}
	return C;
}

List or(List A, List B)
{
	List C;
	ElementType e;
	Position p, q, r;
	
	C = copy(A);
	for (p = First(B); p ; p = Advance(p)) {
		e = Retrieve(p);
		if (!Find(e, C)) {
			ListAddTail(e, C);
		}
	}
	return C;
}

/* TODO
 * Maybe sorting Array first, then insert elements into list,
 * and do action is more efficient. Logic of and or should be
 * rewrite.
 */
main()
{
	List A;
	List B;
	List C;
	List D;
	ElementType a[] = {1, 3, 5, 6, 7, 8, 9};
	ElementType b[] = {2, 4, 5, 8};

	A = InitList(a, NELEMS(a));
	B = InitList(b, NELEMS(b));
	C = and(A, B);
	D = or(A, B);

	PrintList(A);
	PrintList(B);
	PrintList(C);
	PrintList(D);

	/*
	 * TODO release lists
	 */
	
	return;
}
