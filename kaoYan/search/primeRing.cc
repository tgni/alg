/* coding.pdf Page 153
 * prime ring: sum of each two adjacent numbers should be a prime.
 * the first number should always be 1.
 * input:
 *	n (1 < n < 17)
 * output:
 *	output every cases, one line one case.
 */

#include <stdio.h>
#include <string.h>

#define ANS_MAX		(16)
int ans[ANS_MAX];
bool hash[ANS_MAX];
int N;		//input n
int Total;	//total case numbers

#define NR_PRIME	(13)
int prime[NR_PRIME] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

bool judge(int x)
{
	for (int i = 0; i < NR_PRIME; ++i) {
		if (prime[i] == x)
			return true;
	}
	return false;
}

void check(void)
{
	if (judge(ans[N] + ans[1]) == false)
		return;
	for (int i = 1; i <= N; ++i)
		printf("%d%c", ans[i], i == N ? '\n':' ');
	++Total;
}

void DFS(int num)
{
	if (num > 1) {
		if (judge(ans[num]+ans[num-1]) == false)
			return;
	}

	if (num == N) {
		check();
		return;
	}

	for (int i = 2; i <= N; ++i) {
		if (hash[i] == false) {
			hash[i] = true;
			ans[num+1] = i;
			DFS(num+1);
			hash[i] = false;	//backtrack hash[i]
		}
	}
}

int main(void)
{
	int idx = 0;

	while (scanf("%d", &N) != EOF) {
		++idx;
		Total = 0;
		for (int i = 0; i < ANS_MAX; ++i)
			hash[i] = false;

		printf("Case %d:\n", idx);
		ans[1] = 1;
		hash[1] = true;
		DFS(1);
		printf("Total: %d\n", Total);
		printf("\n");
	}

	return 0;
}
