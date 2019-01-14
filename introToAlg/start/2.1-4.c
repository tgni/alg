#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "tool.h"

int32_t addc(int32_t A[], int32_t B[], int32_t C[], int32_t N)
{
	int32_t i, c = 0;

	for (i = N - 1; i >= 0; --i) {
		C[i+1] = A[i] + B[i] + c;

		switch (C[i+1]) {
		case 0:
		case 1:
			c = 0;
			break;
		case 2:
			C[i+1] = 0;
			c = 1;
			break;
		case 3:
			C[i+1] = 1;
			c = 1;
			break;
		default:
			printf("error inputs: a[%d]=%d, b[%d]=%d.\n", i, A[i], i, B[i]);
			break;
		}
	}
	C[i+1]  = c;

	return c;
}

int32_t get_len(int32_t N)
{
	int32_t len = 0;

	while (N) {
		++len;
		N >>= 1;
	}

	return len;
}

void number2array(int32_t N, int32_t A[], int32_t len)
{
	int32_t i = len - 1;

	while (N) {
		A[i--] = N & 1;
		N >>= 1;
	}

	return;
}

int32_t array2number(int32_t A[], int32_t len)
{
	int32_t N = 0, i;

	for (i = 0; i < len; ++i) {
		N <<= 1;
		N |= A[i];
	}

	return N;
}

int32_t main(int32_t argc, char *argv[])
{
	int32_t i, a, b, c, *A, *B, *C, N;

	if (argc != 3) {
		printf("Usage: ./test <a> <b>\n");
		return -1;
	}

	a = strtoul(argv[1], NULL, 0);
	b = strtoul(argv[2], NULL, 0);

	N = get_len(MAX(a, b));

	if (!(A = malloc(N * sizeof(int32_t)))) {
		printf("error at %d\n", __LINE__);
		return -1;
	}
	if (!(B = malloc(N * sizeof(int32_t)))) {
		printf("error at %d\n", __LINE__);
		return -1;
	}
	if (!(C = malloc((N+1) * sizeof(int32_t)))) {
		printf("error at %d\n", __LINE__);
		return -1;
	}

	printf("a: %d b: %d len: %d\n", a, b, N);

	memset(A, 0, sizeof(int32_t) * N);
	memset(B, 0, sizeof(int32_t) * N);
	memset(C, 0, sizeof(int32_t) * (N+1));

	number2array(a, A, N);
	number2array(b, B, N);

	print_array("A:   ", A, N);
	print_array("B:   ", B, N);

	addc(A, B, C, N);

	print_array("C: ", C, N+1);

	c = array2number(C, N+1);
	printf("c: %d\n", c);

	free(A);
	free(B);
	free(C);

	return 0;
}
