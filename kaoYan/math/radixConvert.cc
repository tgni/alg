#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	int i, m, n, bits;
	unsigned long x, y;
	char str[64];

	while (scanf("%d%s%d", &m, str, &n) != EOF) {
		if (m == 0 || n == 0)
			break;

		x = strtoul(str, NULL, m);	
		do {
			y = x % n;
			str[bits++] = (y<10) ? y+'0' : y-10+'A';
			x /= n;
		} while (x != 0);

		for (i = bits-1; i >= 0; --i)
			printf("%c", str[i]);
		printf("\n");
	}

	return 0;
}
