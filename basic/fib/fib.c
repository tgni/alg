/*
 * fib.c
 *
 * Description:
 *	describe Fibonacci numbers calculation
 *      Fibonacci numbers is as follows:
 *      F0 = 1, F1 = 1, F2 = 2, F3 = 3,
 *      F4 = 5, ... , Fi = Fi-1 + Fi-2
 *
 * Author: Daniel Ni
 */

#include <stdio.h>
#include <stdlib.h>

int Fib(int f[], int n)
{
	int i;

	if (n >= 1) {
		f[0] = 1;	
		f[1] = 1;
	} else {
		f[0] = 1;
		return;
	}

	for (i = 2; i < n; ++i) {
		f[i] = f[i-1] + f[i-2];
	}
	return f[i];
}

int fib_n(int n)
{
	int f, f0, f1, i;

	if (n <= 1) {
		return 1;	
	}

	f0 = 1; f1 = 1;

	for (i = 2; i <= n; ++i) {
		f = f0 + f1;	
		f0 = f1;
		f1 = f;
	}
	return f;
}


int main(int argc, char *argv[])
{
	int n, i, *fib;

	if (argc < 2 || argc > 2) {
		printf("Usage: ./fib <N>");
		return -1;
	}
	
	n = strtoul(argv[1], NULL, 0);

	fib = malloc(sizeof(int) * (n + 1));
	if (!fib) {
		printf("malloc failed!\n");
		return -1;
	}

	Fib(fib, n+1);
	for (i = 0; i < (n + 1); ++i)
		printf("%d ", *(fib + i));
	printf("\n");
	printf("fib[%d]: %d\n", n, fib_n(n));

	return 0;
}
