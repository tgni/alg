#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100000
#define MAXL 1000000

int prime[MAXN];	//sequence of prime
unsigned char check[MAXL];

int main(void)
{
	int n, count, i, j;
	while (~scanf("%d", &n)) {
		memset(check, 0, sizeof(check));
		count = 0;	//count for prime
		for (i = 2; i <= n; i++) {
			if (!check[i])
				prime[count++] = i;	//record prime i

			for (j = 0; j < count; j++) {
				if (i*prime[j] > MAXL)
					break;		//too large and break 
				check[i*prime[j]] = 1;	// current i mutiply prime[j] is composite number
				if ((i%prime[j]) == 0)  // if i is one composite, and prime[j] divided i.
					break;
			}
		}

		for (i = 0; i < count; i++)
			printf("%d ", prime[i]);
		printf("\n");
	}
	return 0;
}

#if 0
#include <math.h>
int main(void)
{
	int n, i, j;
	unsigned char *mark;

	while (scanf("%d", &n) != EOF) {
		printf("mallocing size %d\n", n);
		if (!(mark = (unsigned char *)malloc(n+1))) {
			printf("failed to malloc size %d\n", n);
			return -1;
		}
		printf("mallocing ok %d\n", n);

		memset(mark, 0, n+1);
		for (i = 2; i <= n; ++i) {
			if (mark[i])
				continue;
			if (i >= (int)sqrt(n)+1)
				continue;
			for (j = i*i; j <= n && j > 0; j += i) {
				//printf("%d\n", j);
				mark[j] = 1;
			}
		}

		for (i = 2; i < n; ++i) {
			if (!mark[i])
				printf("%d ", i);
		}
		printf("\n");

		free(mark);
	}
	return 0;
}
#endif
