#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"
#include "tool.h"

int main(int argc, char *argv[])
{

	AvlTree T;
	Position P;
	int i, nr;
	int *A;

	if (argc < 2) {
		printf("Usage: ./test <NUM>\n");
		return -1;
	}

	if ((nr = strtoul(argv[1], NULL, 0)) <= 0) {
		printf("NUM must be great than 0\n");
		return -1;
	}

	if (!(A = malloc(sizeof(int) * nr))) {
		printf("malloc failed\n");
		return -1;
	}

	for (i = 0; i < nr; ++i)
		A[i] = i;
	shuffle(A, nr);

	T = MakeEmpty( NULL );
	for (i = 0; i < nr; ++i)
		T = Insert(A[i], T);

	ComputeDistAndDepth(T);
	PrintAvlTree(T);
/*
	for (i = nr - 1; i >= 0; --i) {
		T = Delete(A[i], T);
		ComputeDistAndDepth(T);
		PrintAvlTree(T);
	}
*/
	//printf( "Min is %d, Max is %d\n", Retrieve( FindMin( T ) ),
	//	Retrieve( FindMax( T ) ) );

	return 0;
}
