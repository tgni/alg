#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: ./abs x");
		return -1;
	}

	int x = strtoul(argv[1], 0, 0);

	printf("x=%x, abs(x)=%x, ((x>>30)|1)*x: %x\n", x, abs(x), ((x >> 30) | 1) * x);
	return 0;
}
