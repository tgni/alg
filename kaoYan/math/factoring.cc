/* Given n, n <= 10^9, calculate its sub prime factors numbers. 
 * a) 1 is not prime.
 * b) if n is prime, the n is its sub prime factor.
 * eg:
 * 10 -> 2, 5
 * 11 -> 11
 * 12 ->  2, 3
 */

#include <stdio.h>

//n is less than 10^9, so mark just less than sqrt(n)
bool mark[100001];
int prime[100001];
int primeSize;

void init(void)
{
	primeSize = 0;
	for (int i = 2; i <= 100000; ++i) {
		if (mark[i] == true) 
			continue;
		prime[primeSize++] = i;
		if (i >= 1000) 
			continue;
		for (int j = i*i; j <= 10000; j += i) {
			mark[j] = true;
		}
	}
}

int main(void)
{
	init();

	int n;
	while (scanf("%d", &n) != EOF) {
		int ansPrime[30];	//answer of factors
		int ansSize = 0;	//factor numbers, no duplicate
		int ansPow[30];		//factors' power

		for (int i = 0; i < primeSize; ++i) {
			if (n % prime[i] == 0) {
				ansPrime[ansSize] = prime[i]; 
				ansPow[ansSize] = 0;
				while (n % prime[i] == 0) {
					ansPow[ansSize]++;
					n /= prime[i];
				}
				ansSize++;
				if (n == 1) break;
			}
		}

		if (n != 1) {
			ansPrime[ansSize] = n;	//max prime factor
			ansPow[ansSize++] = 1;  //max prime factor must be only one. 
						//because we have tested all primes less than sqrt(n).
		}

		int ans = 0;
		printf("prime factors: ");
		for (int i = 0; i < ansSize; ++i) {
			ans += ansPow[i];
			for (int j = 0; j < ansPow[i]; ++j)
				printf("%d ", ansPrime[i]);
		}
		printf("\ntotal: %d\n", ans);
	}

	return 0;
}
