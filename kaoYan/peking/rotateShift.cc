#include <stdio.h>

int main()
{
	unsigned short a, b;

	while (scanf("%hu%hu", &a, &b) != EOF) {
		int cnt;
		for (cnt = 0; a != b && cnt < 16; ++cnt) {
			int msb = b >> 15;
			b = (b << 1) + msb;
		}
		printf("%s\n", cnt == 16 ? "NO" : "YES");
	}

	return 0;
}
