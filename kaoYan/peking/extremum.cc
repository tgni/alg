#include <stdio.h>

int main()
{
	int k;
	while (scanf("%d", &k) != EOF) {
		int a[k];
		for (int i = 0; i < k; ++i)
			scanf("%d", &a[i]);

		for (int i = 0; i < k; ++i) {
			if (i == 0) {
				if (a[i] != a[i+1])
					printf("%d ", i);
			} else if (i == k-1) {
				if (a[i] != a[i-1])
					printf("%d ", i);
			} else {
				if ((a[i] > a[i-1] && a[i] > a[i+1]) || 
				    (a[i] < a[i-1] && a[i] < a[i+1]))
					printf("%d ", i);
			}
		}
	}

	return 0;
}
