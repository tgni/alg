/*
Ҫ��һ����ά���������Ӿ�������Ҫ��һά���������Ӿ��󣨼�һά�����������ͣ�
����ԭ��ά���������Ӿ������ڵ���Ϊi��j
  1 ��i = jʱ��������Ӿ���Ϊ��i�е���������
  2 ��i != jʱ�����������Ѿ��õ�����Ӿ�����У�Ҫ����������ڵ���
      ���ǰѴӵ�i�е���j�е�Ԫ�ذ�����ӣ��õ�һ��ֻ��һ�е�һά���飬���һά����
      ���������;�������Ӿ���
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
