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

long long fib(long long n)
{
	long long f, f0, f1; 
	int i;

	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;	

	f0 = 0; f1 = 1;

	for (i = 2; i <= n; ++i) {
		f = f0 + f1;	
		f0 = f1;
		f1 = f;
	}
	return f;
}


int main(void)
{
	int n;

	while (scanf("%d", &n) != EOF)
		printf("%lld\n", fib(n));

	return 0;
}
