#include <stdio.h>
#include "types.h"


int find_median(int A[], int B[], int n)
{
	int mid_a, low_a, high_a;
	int mid_b, low_b, high_b;

	low_a = low_b = 0;
	high_a = high_b = n-1;
	mid_a = mid_b = (low_a + high_a) / 2;

	while (low_a <= high_a && low_b <= high_b) {
		if (A[mid_a] == B[mid_b])
			break;
		if (high_a == low_a) // or high_b == low_b 
			break;

		if (A[mid_a] < B[mid_b]) {
			low_a  = mid_a + 1;
			high_b = mid_b - 1;
		} else {
			high_a = mid_a - 1;
			low_b  = mid_b + 1; 
		}

		mid_a = (low_a + high_a) / 2;
		mid_b = (low_b + high_b) / 2;
	}
	
	return MIN(A[mid_a], B[mid_b]);
}

int find_median_std(int A[], int B[], int n)
{
	int la, ma, ha;
	int lb, mb, hb;

	la = lb = 0;
	ha = hb = n - 1;

	while (la != ha || lb != hb) {
		ma = (la + ha) / 2;	
		mb = (lb + hb) / 2;

		if (A[ma] == B[mb])
			return A[ma];

		if (A[ma] < B[mb]) {
			if ((la + ha) % 2 == 0)	{ //nr is odd
				la = ma; 
				hb = mb;
			} else {
				la = ma+1;
				hb = mb;
			}
		} else {
			if ((lb + hb) % 2 == 0)	{ //nr is odd
				ha = ma; 
				lb = mb;
			} else {
				ha = ma;
				lb = mb+1;
			}
		}
	}

	return MIN(A[la], B[lb]);
}

int main()
{
	int A[] = {11, 13, 14, 15, 17, 19};
	int B[] = {2, 4, 6, 8, 13, 20};

	printf("median is %d, %d\n", find_median(A, B, 5), find_median_std(A, B, 6));

	return 0;
}
