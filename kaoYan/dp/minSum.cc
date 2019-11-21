#include <stdio.h>
#include <algorithm>

using namespace std;

int MinSubsequenceSum(const int A[ ], int N)
{
	int ThisSum, MinSum, i, j, k;

	MinSum = 0;
	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			ThisSum = 0;
			for( k = i; k <= j; k++ )
				ThisSum += A[ k ];

			if (ThisSum < MinSum)
				MinSum = ThisSum;
		}
	}

	return MinSum;
}


int main(void)
{
	int a[] = {10, 20, -10, 8, -30, 20};

	printf("min: %d\n", MinSubsequenceSum(a, 6));

	return 0;
}
