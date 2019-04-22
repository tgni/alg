#include <stdio.h>

int main()
{
	double a[12];
	while (scanf("%lf", &a[0]) != EOF) {
		for (int i = 1; i < 12; ++i)
			scanf("%lf", &a[i]);
		double sum = 0;
		for (int i = 0; i < 12; ++i)
			sum += a[i];

		sum /= 12.0;
		printf("$%.02lf\n", sum);
	}

	return 0;
}
