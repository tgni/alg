#include <stdio.h>
#include <string.h>

#define MAXN 100000
#define MAXL 1000000

int prime[MAXN];
unsigned char check[MAXL];

int main(void)
{
	int n, count, i, j;
	while (~scanf("%d", &n)) {
		memset(check, 0, sizeof(check));
		count = 0;
		for (i = 2; i <= n; i++) {
			if (!check[i])
				prime[count++] = i;

			for (j = 0; j < count; j++) {
				if (i*prime[j] > MAXL)
					break; // 过大的时候跳出
				check[i*prime[j]] = 1;
				if ((i%prime[j]) == 0) // 如果i是一个合数，而且i % prime[j] == 0
					break; 
			}
		}

		for (i = 0; i < count; i++)
			printf("%d ", prime[i]);
		printf("\n");
	}
	return 0;
}
