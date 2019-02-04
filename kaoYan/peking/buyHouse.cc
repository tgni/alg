#include <stdio.h>

int main()
{
	int n, k;

	while (scanf("%d%d", &n, &k) != EOF) {
		float price = 200;
		int m = 1;

		while (m * n < price && m <= 21) {
			price = price + price / 100 * k;
			++m;
		}
		if (m > 21)
			printf("Impossible\n");
		else
			printf("%d\n", m);
	}

	return 0;
}
