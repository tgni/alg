/* Description:
 *	Given A and B, compute A^B, and output its last three numbers as an 
 *	integer(Decimental). 1 <= A, B <= 10000, if A=0 and B=0 end program. 
 */

#include <stdio.h>

int main(void)
{
	int a, r;
	unsigned int b;

	while (scanf("%d%d", &a, &b) != EOF) {
		if (a == 0 && b == 0)
			break;
		r = 1;	
		while (b != 0) {
			if (b&1) {
				r *= a;
				r %= 1000;
			}
			b >>= 1;
			a *= a;
			a %= 1000;
		}
		printf("%d\n", r);
	}

	return 0;
}
