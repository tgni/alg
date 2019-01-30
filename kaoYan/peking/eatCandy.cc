#include <stdio.h>

int fib(int n)
{
	if (n == 1)
		return 1;
	else if (n == 2)
		return 2;

	int a = 1, b = 2, c;
	for (int i = 3; i <= n; ++i) {
		c = a + b;
		a = b;
		b = c;
	}

	return c;
}

int main()
{
	int n;

	while (scanf("%d", &n) != EOF) {
		printf("%d\n", fib(n));
	}

	return 0;
}
