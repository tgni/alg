#include <stdio.h>


void print_array(int A[], int len);

double findMedianSortedArrays(int* A, int m, int* B, int n)
{
        int i, j, imin, imax, half_len, max_left, min_right, tmp, *temp;

        if (m > n) {
                temp = A; A = B; B = temp; 
                tmp = m; m = n; n = tmp;
        }

	printf("A is "); print_array(A, m);
	printf("B is "); print_array(B, n);

        imin = 0; imax = m; half_len = (m+n+1)/2;
        while (imin <= imax) {
                i = (imin + imax)/2;
                j = half_len - i;
                if (i < imax && B[j-1] > A[i]) {
                        imin = i + 1;
                } else if (i > imin && A[i-1] > B[j]) {
                        imax = i - 1;
                } else {
                        if (i == 0) {
                                max_left = B[j-1];      //A[i-1] not exist
                        } else if (j == 0) {
                                max_left = A[i-1];      //B[j-1] not exist
                        } else {
                                max_left = (A[i-1] < B[j-1]) ? B[j-1] : A[i-1];
                        }
                        
                        if (i == m) {
                                min_right = B[j];       //A[m] not exist
                        } else if (j == n) {
                                min_right = A[i];       //B[n] not exist
                        } else {
                                min_right = (A[i] < B[j]) ? A[i] : B[j];
                        }

			printf("i: %d j: %d max_left: %d min_right: %d\n", i, j, max_left, min_right);
                        
                        if ((m+n)%2 == 1)
                               return max_left; 

                        return (max_left + min_right) / 2.0;
                }
        }
        
        return 0.0;
}

void print_array(int A[], int len)
{
	int i;

	for (i = 0; i < len; ++i)
		printf("%d ", A[i]);
	printf("\n");
}

int main(void)
{
	int A[2] = {1, 3};
	int B[1] = {2};
	double median;

	printf("A is "); print_array(A, 2);
	printf("B is "); print_array(B, 1);
	
	printf("find median sorted arrays>\n");
	median = findMedianSortedArrays(A, 2, B, 1);
	printf("median is: %f\n", median);

	return 0;
}
