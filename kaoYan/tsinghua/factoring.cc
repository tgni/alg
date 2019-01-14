#include <stdio.h>

//n is less than 10^9, so mark just less than sqrt(n)
bool mark[100001];
int prime[100001];
int primeSize;
int number[1000];

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
		for (int i = 0; i < n; ++i)
			scanf("%d", &number[i]);

		for (int i = 0; i < n; ++i) {

			int ansPrime[30];	//answer of factors
			int ansSize = 0;	//factor numbers, no duplicate
			int ansPow[30];		//factors' power

			for (int j = 0; j < primeSize; ++j) {
				if (number[i] % prime[i] == 0) {
					ansPrime[ansSize] = prime[j]; 
					ansPow[ansSize] = 0;
					while (number[i] % prime[j] == 0) {
						ansPow[ansSize]++;
						number[i] /= prime[j];
					}
					ansSize++;
					if (number[i] == 1) break;
				}
			}

			if (number[i] != 1) {
				ansPrime[ansSize] = number[i];	//max prime factor
				ansPow[ansSize++] = 1;  //max prime factor must be only one. 
			}

			int ans = 1;
			for (int j = 0; j < ansSize; ++j)
				ans *= (ansPow[i]+1);
			printf("%d\n", ans);

		}
	}

	return 0;
}
