#include <stdio.h>

int S[11] = {1, 3, 0, 5, 3, 5, 6,  8,  8,  2,  12};
int F[11] = {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16};

struct activity_s {
	int k;
	int s, f;
} A[12];

int greedy_activity_selector(int s[], int f[], struct activity_s *a, int n) 
{
	int k = 0, m, i = 0;
	//int k = 1, m, i = 0; /* another solution from k = 1 */

	a[i].k = k;
	a[i].s = s[k];
	a[i].f = f[k];
	i++;

	for (m = 1; m < n; ++m) {
		if (s[m] >= f[k]) {
			a[i].k = m;
			a[i].s = s[m];
			a[i].f = f[m];
			i++;
			k = m;
		}
	}

	return i;
}

int main()
{
	int i, n;

	n = greedy_activity_selector(S, F, A, 11);
	
	for (i = 0; i < n; ++i) {
		printf("%d: %d %d\n", A[i].k, A[i].s, A[i].f);
	}

	return 0;
}
