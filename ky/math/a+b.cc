/* 
 * description: input two number a and b, output a+b's m radix number sequence.
 * 1 < m < 10, and if m == 0, end program.
 */

#include <stdio.h>

int main(void)
{
	int i, m, bits;
	long long a, b, sum;
	unsigned char str[64];

	while (scanf("%d", &m) != EOF) {
		if (m == 0)
			break;

		scanf("%lld%lld", &a, &b);
		sum = a+b;
		bits = 0;
		do {
			str[bits++] = sum % m;
			sum /= m;
		} while (sum != 0);	//if sum is 0, str[0]=0

		for (i = bits-1; i >= 0; --i) 
			printf("%d", str[i]);
		printf("\n");
	}

	return 0;
}
