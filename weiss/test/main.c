#include <stdio.h>
#include "tree.h"

#define ROOT	0
#define LEFT    1	
#define RIGHT	2

static const char *pos[] = {
	"root",
	"l",
	"r"
};

#if 0
void PrintVal(Position p, int depth, int flag)
{
	int i;

	for (i = 0; i < depth; ++i)
		printf("\t");

	printf("%2d(%s)\n", Retrieve(p), pos[flag]);

	return;
}

void listVal(SearchTree st, int depth, int flag)
{
	if (st) {
		PrintVal(st, depth, flag);
		if (st->Left) {
			listVal(st->Left, depth+1, LEFT);
		}
		if (st->Right) {
			listVal(st->Right, depth+1, RIGHT);
		}
	}

	return;
}

void listTree(SearchTree st)
{
	listVal(st, 0, ROOT);
}
#endif


void PrintVal(Position p, int depth, int flag)
{
	int i;

	for (i = 0; i < depth; ++i)
		printf("\t");

	printf("%2d(%s)\n", Retrieve(p), pos[flag]);

	return;
}

void listVal(SearchTree st, int depth, int flag)
{
	if (st) {
		PrintVal(st, depth, flag);
		if (st->Left) {
			listVal(st->Left, depth+1, LEFT);
		}
		if (st->Right) {
			listVal(st->Right, depth+1, RIGHT);
		}
	}

	return;
}

void listTree(SearchTree st)
{
	listVal(st, 0, ROOT);
}

int main(void)
{
	int a[] = {3, 1, 4, 6, 9, 2, 5, 7};
	int i;
	SearchTree st;

	for (i = 0; i < sizeof(a)/sizeof(int); ++i)
		st = Insert(a[i], st);

	listTree(st);

	while (st) {
		printf("index: %d, Delete: %d\n", i, st->Element);
		st = Delete(st->Element, st);
		printf("--------------------------\n");
		listTree(st);
		printf("--------------------------\n");
	}

	return 0;
}
