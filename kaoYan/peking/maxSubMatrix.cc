/*
要求一个二维矩阵的最大子矩阵，首先要求一维矩阵的最大子矩阵（即一维数组连续最大和）
假设原二维矩阵的最大子矩阵所在的行为i到j
  1 当i = j时，则最大子矩阵为第i行的连续最大和
  2 当i != j时，现在我们已经得到最大子矩阵的行，要求的是其所在的列
      我们把从第i行到第j行的元素按列相加，得到一个只有一行的一维数组，则该一维数组
      的连续最大和就是最大子矩阵。
*/

#include <stdio.h>

#define INF	(0x7F)
#define max(a, b) ((a > b) ? a : b)

int matrix[101][101];
int A[101];

int maxSubSum(int i, int j, int n)
{
	long maxSum = -INF, sum = 0;

	for (int l = 1; l <= n; ++l) {
		A[l] = 0;
		for (int k = i; k <= j; ++k)
			A[l] += matrix[k][l];
	}

	for (int i = 1; i <= n; ++i) {
		sum = max(0, sum) + A[i];
		maxSum = max(sum, maxSum); 
	}

	return maxSum;
}

int main()
{
	int n;

	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j)
				scanf("%d", &matrix[i][j]);
		}

		int maxSum = -INF, sum = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				sum = maxSubSum(i, j, n);
				maxSum = max(sum, maxSum);
			}
		}
		printf("%d", maxSum);
	}

	return 0;
} 
