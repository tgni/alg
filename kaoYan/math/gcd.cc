#include <stdio.h>

int gcd(int a, int b)
{
	int tmp;

	if (a == 0 && b == 0)
		return -1;

	if (b > a) {
		tmp = a;
		a  = b;
		b = tmp;
	}

	while (b > 0) {
		tmp = a % b;
		a = b;
		b = tmp;
	}

	return a;
}

int main(void)
{
	int a, b;

	while (scanf("%d%d", &a, &b) != EOF)
		printf("a: %d b: %d, gcd: %d\n", a, b, gcd(a, b));

	return 0;
}
