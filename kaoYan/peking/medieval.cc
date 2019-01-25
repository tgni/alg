#include <stdio.h>
#include <algorithm>

using namespace std;

int A[10001];

int main()
{
	int n;

	while (scanf("%d", &n) != EOF) {
		if (n == 0)
			break;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &A[i]);
		}
		sort(A, A+n);
		if (n % 2)
			printf("%d\n", A[n/2]);
		else
			printf("%d\n", (A[n/2-1]+A[n/2])/2);
	}

	return 0;
}
