/* given N, output N's factorial. N is less than 1000.
 */

#include <stdio.h>

int main()
{
	int n;

	while (scanf("%d", &n) != EOF) {
		int ans = 1;
		for (int i = 1; i <= n; ++i)
			ans *= i;
		printf("%d\n", ans);
	}
	return 0;
}
