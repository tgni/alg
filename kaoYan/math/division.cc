/* given n, a, provide such max k to satisfy n! can be divided by a^k and not be divided
 * by a^(k+1)
 * eg: 6, 10 -> 1
 */

#include <stdio.h>

int prime[1001];
int primeSize;
bool mark[1001];

int cnt1[1000];	//cnt1[i] save power of sub prime[i] factor of n!
int cnt2[1000]; //cnt2[i] save power of sub prime[i] factor of a

/* get primes of less than 1000 */
void init(void)
{
	primeSize = 0;
	for (int i = 0; i <= 1001; ++i)
		mark[i] = false;

	for (int i = 2; i <= 1000; ++i) {
		if (mark[i] == true)
			continue;
		prime[primeSize++] = i;

		if (i > 33) //33 great than sqrt(1000)
			return;
		for (int j = i*i; j <= 1000; j += i)
			mark[j] = true;
	}
}

int main(void)
{
	init();

	int n, a;
	while (scanf("%d%d", &n, &a) != EOF) {
		for (int i = 0; i < primeSize; ++i)
			cnt1[i] = cnt2[i] = 0;

		for (int i = 0; i < primeSize; ++i) {
			int t = n;
			while (t) {
				cnt1[i] += t / prime[i];
				t = t/prime[i];
			} // calculate t/prime[i]^k, loop sum, until t/prime[i]^k == 0
		}

		int k = 0x7fffffff; 
		for (int i = 0; i < primeSize; ++i) {
			while (a % prime[i] == 0) {
				cnt2[i]++;
				a /= prime[i];
			} // calculate prime[i]'s power as a prime factor of 'a'

			if (cnt2[i] == 0) continue;	//not a factor

			if (cnt1[i]/cnt2[i] < k)
				k = cnt1[i]/cnt2[i];	//get minimum k
		}
		printf("%d\n", k);
	}

	return 0;
}
