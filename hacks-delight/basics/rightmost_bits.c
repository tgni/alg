#include <stdio.h>
#include <stdlib.h>

void print_binary(int x)
{
	int i;

	for (i = 31; i >= 0; --i) {
		printf("%d", (x >> i) & 1);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	int x;

	if (argc < 2) {
		printf("usage: ./shift [x]\n");
		return -1;
	}

	x = strtoul(argv[1], NULL, 0);
	printf("x:");
	print_binary(x);
	printf("x & (x-1):");
	print_binary(x & (x-1));
	printf("x | (x+1):");
	print_binary(x | (x+1));
	printf("x & (x+1):");
	print_binary(x & (x+1));
	printf("x | (x-1):");
	print_binary(x | (x-1));
	printf("~x & (x+1):");
	print_binary(~x & (x+1));
	printf("~x | (x-1):");
	print_binary(~x | (x-1));

	printf("trailing 0 to 1\n");
	printf("~x & (x-1):");
	print_binary(~x & (x-1));
	printf("~(x | -x):");
	print_binary(~(x | -x));
	printf("(x & -x)-1:");
	print_binary((x & -x)-1);
	printf("trailing 1 to 0\n");
	printf("~x | (x+1):");
	print_binary(~x | (x+1));

	return 0;
}
