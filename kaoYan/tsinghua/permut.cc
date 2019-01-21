#include <stdio.h>

/* Given a0, a1, p, q, k
 * an = p*a(n-1) + q*a(n-2)
 */

int main()
{
	long a0, a1, p, q, k;
	while (scanf("%ld%ld%ld%ld%ld", &a0, &a1, &p, &q, &k) != EOF) {
		if (k == 0) {
			printf("%ld\n", a0 % 10000);
			continue;
		} else if (k == 1) {
			printf("%ld\n", a1 % 10000);
			continue;
		}

		long a;
		for (int i = 2; i <= k; ++i) {
			a = (p * a1 + q * a0) % 10000;
			a0 = a1;
			a1 = a;
		}

		printf("%ld\n", a);
	}

	return 0;
}
