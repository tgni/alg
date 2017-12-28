#include <stdio.h>
/* 
 * fibonacci series
 * f(0) = 1, f(1) = 1, f(2) = f(0) + f(1) 
 * f(n) = f(n - 1) + f(n - 2)
 */
int fib(int n)
{
	unsigned long long i, a = 1, b = 1, c = 0;
	
	if (n <= 1)
		return 1;
	
	for (i = 2; i <= n; ++i) {
		c = a + b;
		a = b;
		b = c;
		printf("%llu, ", c);
	}
	printf("\n");

	return c;
}

main(int argc, char *argv[])
{
	int n;

	if (argc < 2) {
		return -1;
	}

	n = strtoul(argv[1], NULL, 0);
	fib(n);

	return 0;
}
