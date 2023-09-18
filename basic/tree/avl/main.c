/* 4.16 Show the result of inserting 2,1,4,5,9,3,6,7 into an initially empty AVL tree */

#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"
#include "tool.h"

int main(int argc, char *argv[])
{
	AvlTree T;
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
		A[i] = i+1;
	//shuffle(A, nr);

	T = MakeEmpty( NULL );
	for ( i = 0; i < nr; ++i)
		T = Insert(A[i], T);

	ComputeDistAndDepth(T);
	HPrintAvlTree(T);
	//InOrder(T);
	//PreOrder(T);
	//PostOrder(T);
	printf("Height: %d\n", GetHeight(T));

	return 0;
}
