/* me.c
 * Description:
 *	Modular Exponentiation
 * History:
 *	Sep 1, 2017	tgni	Create
 */

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

int32_t mod_exp(uint32_t b, uint32_t exp, uint32_t m)
{
	int32_t x, pow;

	x = 1;
	pow = b % m;

	for (; exp; exp >>= 1) {
		if (exp & 1)
			x = (x * pow) % m;
		pow = (pow * pow) % m;
	}

	return x;
}

ulong_t power(uint32_t b, uint32_t exp)
{
	if (exp == 0)
		return 1;
	if (exp == 1)
		return b;
	if (!(exp%2))
		return power(b*b, exp/2);
	else
		return power(b*b, exp/2) * b; 
}

int32_t main(int32_t argc, char *argv[])
{
	int32_t b, exp, div;
	ulong_t x, rem;
	
	if (argc != 4) {
		printf("Usage: ./me <base> <exp> <div>\n");
		return -1;
	}

	b   = strtoul(argv[1], NULL, 0);
	exp = strtoul(argv[2], NULL, 0);
	div = strtoul(argv[3], NULL, 0);

	x   = power(b, exp);
	rem = x % div;

	printf("%lu mod %d = %lu\n", x, div, rem);

	rem = mod_exp(b, exp, div);

	printf(" mod exp: %lu\n", rem);

	return 0;
}
