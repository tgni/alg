#include <stdio.h>

#define max(a, b) ((a > b) ? a : b)

int Price[11] =  {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

int cut_rot(int p[], int n)
{
	int q = -1;
	int i;

	if (n == 0)
		return 0;
	for (i = 1; i <= n; ++i) {
		q = max(q, p[i] + cut_rot(p, n - i));
	}
	return q;
}

int memorized_cut_rod_aux(int p[], int n, int r[])
{
	int i, q;

	if (r[n] >= 0)
		return r[n];

	if (n == 0) {
		q = 0;
	} else {
		q = -1;
		for (i = 1; i <= n; ++i)
			q = max(q, p[i] + memorized_cut_rod_aux(p, n-i, r));
	}
	r[n] = q;

	return q;
}

int memorized_cut_rod(int p[], int n)
{
	int i;
	int r[11];

	if (n > 10)
		return -1;

	for (i = 0; i <= n; ++i) {
		r[i] = -1;
	}
	return memorized_cut_rod_aux(p, n, r);
}

int bottom_up_cut_rod(int p[], int n)
{
	int r[11];
	int i, j, q;

	r[0] = 0;
	for (j = 1; j <= n; ++j) {
		q = -1;
		for (i = 1; i <= j; ++i) {
			q = max(q, p[i] + r[j-i]);
		}
		r[j] = q;
	}

	return r[n];
}

int extended_bottom_up_cut_rod(int p[], int n, int r[], int s[])
{
	int i, j, q;

	r[0] = 0;

	for (j = 1; j <= n; ++j) {
		q = -1;
		for (i = 1; i <= j; ++i) {
			if (q < p[i] + r[j-i]) {
				q = p[i] + r[j-i];
				s[j] = i;
			}
			r[j] = q;
		}
	}
	return r[n];
}

int print_cut_rot_solution(int p[], int n)
{
	int r[11], s[11];

	extended_bottom_up_cut_rod(p, n, r, s);

	while (n > 0) {
		printf("%d ", s[n]);
		n = n - s[n];
	}
	printf("\n");

	return r[n];
}

int main()
{
	int i;

	for (i = 1; i < 11; ++i) {
		printf("r%d: %d\n", i, cut_rot(Price, i));
	}
	for (i = 1; i < 11; ++i) {
		printf("mr%d: %d\n", i, memorized_cut_rod(Price, i));
	}
	for (i = 1; i < 11; ++i) {
		printf("br%d: %d\n", i, bottom_up_cut_rod(Price, i));
	}
	for (i = 1; i < 11; ++i) {
		print_cut_rot_solution(Price, i);
	}


	return 0;
}
