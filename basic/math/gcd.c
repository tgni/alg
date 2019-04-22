#include <stdio.h>

/* Euclid's algorithm */
unsigned int Gcd(unsigned int M, unsigned int N)
{
	unsigned int Rem;

	while (N > 0) {
		Rem = M % N;	
		M = N;
		N = Rem;
	}

	return M;
}

/* JiuZhang SuanShu (¾ÅÕÂËãÊõ) */
unsigned int Gcd2(unsigned int M, unsigned int N)
{
	unsigned int S;

	/* M and N are both pair */
	if (!(M % 2) && !(N % 2)) {
		M = M / 2;
		N = N / 2;
	} 

	while (M != N) {
		if (M > N) {
			M = M - N;
		} else {
			N = N - M;
		}
	}

	return M;
}

int main(int argc, char *argv[])
{
	unsigned int M, N;

	if (argc < 3) {
		printf("please input two numbers as parameters.\n");
		return -1;
	}

	M = strtoul(argv[1], 0, 0);
	N = strtoul(argv[2], 0, 0);

	printf("M %d N %d gcd %d gcd2 %d\n", M, N, Gcd(M, N), Gcd2(M, N));

	return 0;
}
