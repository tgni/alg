#include <stdio.h>
#include <algorithm>

using namespace std;

int A[601];

int gcd(int a, int b)
{
	int tmp;

	if (b > a)
		swap(a, b);

	while (b > 0) {
		tmp = a % b;
		a = b;
		b = tmp;
	}

	return a;
}

int main()
{
	int n;

	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i) {
			scanf("%d", &A[i]);
		}
		int cnt = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				if (gcd(A[i], A[j]) == 1)
					++cnt;
			}
		}
		printf("%d\n", cnt);
	}

	return 0;
}
	
