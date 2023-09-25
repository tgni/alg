#include "fatal.h"
#include "binheap.h"

ElementType X[8] = {
	{'a', 45, 0, NULL, NULL, NULL},
	{'b', 13, 0, NULL, NULL, NULL},
	{'c', 12, 0, NULL, NULL, NULL},
	{'d', 16, 0, NULL, NULL, NULL},
	{'e', 9,  0, NULL, NULL, NULL},
	{'f', 5,  0, NULL, NULL, NULL},
	{'g', 5,  0, NULL, NULL, NULL},
	{'h', 6,  0, NULL, NULL, NULL},
};


ElementType * huffman(void)
{
	int n = sizeof(X) / sizeof(X[0]);
	int i;
	PriorityQueue Q;
	ElementType *x, *y, *z;

	Q = Initialize(n);
	for (i = 0; i < n; ++i) {
		Insert(&X[i], Q);
		printf("Insert x %c %d\n", X[i].c, X[i].p);
	}

	for (i = 1; i <= n - 1; ++i) {
		if (!(z = malloc(sizeof(ElementType))))
			FatalError("Out of space for alloc z!!!");

		z->left = x = DeleteMin(Q);
		z->right = y = DeleteMin(Q);
		x->parent = y->parent = z;
		x->v = 0;
		y->v = 1;
		z->c = 'M';
		z->p = x->p + y->p;
		Insert(z, Q);
	}

	x = DeleteMin(Q);
	x->parent = NULL;
	x->v = 0;

	return  x;
}

void print_huffman(ElementType *T)
{
	if (T) {
		printf("%c %d\n", T->c, T->p);
		if (T->left) {
			printf("e->left: ");
			print_huffman(T->left);
		}
		if (T->right) {
			printf("e->right: ");
			print_huffman(T->right);
		}
	}
}


int main(void)
{
	int i, j;
	int n = sizeof(X) / sizeof(X[0]);
	ElementType *Root;
	ElementType *x;
	struct {
		int code;
		int len;
	} c[n];

	Root = huffman();
	print_huffman(Root);

	for (i = 0; i < n; ++i) {
		x = &X[i];
		printf("%c : ", x->c);
		c[i].code = 0;
		c[i].len = 0;
		while (x != Root) {
			c[i].code |= x->v << c[i].len;
			c[i].len++;
			x = x->parent;
		}
		printf("len: %d code: 0x%x binary: ", c[i].len, c[i].code);

		for (j = c[i].len - 1; j >= 0; --j) {
			printf("%d", (c[i].code >> j) & 1);
		}
		printf("\n");
	}
	return 0;
}
