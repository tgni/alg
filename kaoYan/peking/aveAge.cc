#include <stdio.h>

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		double sum = 0;
		for (int i = 0; i < n; ++i) {
			int age;
			scanf("%d", &age);
			sum += age;
		}
		printf("%.2f", sum/n);
	}

	return 0;
}
