/*
 * CopyRight bala bala
 *
 * File:	sh.c
 * Description:
 *	Avl Tree S(h), S is nodes of Avl Tree, h is height of tree.
 *	S(h) is one like Fibonacci numbers Function as belows:
 *		S(h) = S(h-1) + S(h-2) + 1
 *		for h=0, S(0)=1
 *		    h=1, S(1)=2
 * History:
 *	Feb 8, 2017	Tgni	Create
 */

#include <stdio.h>
#include <stdlib.h>

unsigned long S(int h)
{
	unsigned long f, a, b, i;

	if (h == 0)
		return 1;
	else if (h == 1)
		return 2;
	a = 1; b = 2;

	for (i = 2; i <= h; ++i) {
		f = a + b + 1;	
		a = b;
		b = f;
	}

	return f;
}


int main(int argc, char *argv[])
{
	int h, i;

	if (argc != 2) {
		printf("Usage: ./test <N>");
		return -1;
	}
	
	h = strtoul(argv[1], NULL, 0);
	printf("S[%d]: %ul\n", h, S(h));

	return 0;
}
