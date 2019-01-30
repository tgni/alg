#include <stdio.h>

int main()
{
	int m, n;

	while (scanf("%d%d", &m, &n) != EOF) {
		while (m != n) {
			if (m > n)
				m /= 2;
			else
				n /= 2;
		}
		printf("%d\n", m);
	}

	return 0;
}
