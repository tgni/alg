#include <stdio.h>

int exp_mod(int x, int y, int n)
{
	int ret = 1;

	while (y) {
		if (y&1)
			ret = ((long)ret*x) % n;

		x = ((long)x*x) % n;
		y >>= 1;
	}

	return ret;
}

int main()
{
	int x, y, k, ans;

	while (scanf("%d%d%d", &x, &y, &k) != EOF) {
		ans = exp_mod(x, y, k-1);
		if (ans == 0) ans = k-1;
		printf("%d\n", ans);
	}

	return 0;
}
