#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	char str[64];

	while (scanf("%s", str) != EOF) {
		unsigned long x, y;
		int bits = 0;

		x = strtoul(str, NULL, 16);	

		do {
			y = x % 10;
			str[bits++] = (y<10) ? y+'0' : y-10+'A';
			x /= 10;
		} while (x != 0);

		for (int i = bits-1; i >= 0; --i)
			printf("%c", str[i]);
		printf("\n");
	}

	return 0;
}
