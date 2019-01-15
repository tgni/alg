#include <stdio.h>
#include <string.h>

char proxy[1000][16];
int proxy_map[1000];
char server[5000][16];

int find_max_position(int sm, int em, int n)
{
	for (int i = 0; i < n; ++i) {
		proxy_map[i] = -1;
		for (int j = sm; j < em; ++j) {
			if (strcmp(proxy[i], server[j]) == 0) {
				proxy_map[i] = j;
				break;
			}
		}
	}

	int max = -1;
	for (int i = 0; i < n; ++i) {
		if (proxy_map[i] == -1)
			return -1;
		if (max < proxy_map[i])
			max = proxy_map[i];
	}

	return max;
}

int main(void)
{
	int n, m;

	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i)
			scanf("%s", proxy[i]);
		scanf("%d", &m);
		for (int i = 0; i < m; ++i)
			scanf("%s", server[i]);

		int pos = 0, shift = 0;

		while (pos < m) {
			pos = find_max_position(pos, m, n);
			if (pos == -1)
				break;
			if (n == 1)
				break;
			shift++;
		}

		if (pos != -1 && n == 1)
			printf("-1\n");
		else
			printf("%d\n", shift);
	}

	return 0;
}
