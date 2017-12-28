/*
 * Horner's Rule implementation
 * In China we call it as Alg of QingJiuShao
 * By Daniel Ni
 */ 
#include <stdio.h>
#include <math.h>

int horner(int x, int a[], int n)
{
	int poly = 0, i;

	for (i = n; i >= 0; --i) {
		poly = x * poly + a[i];		
	}
	return poly;
}

int main(void)
{
	/* calculate x = 3, 4x^4  + 8x^3 + x + 2 */
	int a[5] = {2, 1, 0, 8, 4};
	int result ;

	result = 4 * pow(3, 4) + 8 * pow(3, 3) + 3 + 2;

	printf("horner:%d, result:%d\n", horner(3, a, 4), result);

	return 0;
}
