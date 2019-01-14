#include <queue>
#include <cstdio>

using namespace std;

priority_queue<int, vector<int>, greater<int>> Q;

int main(void)
{
	int n;

	while (scanf("%d", &n) != EOF) {
		while (!Q.empty()) Q.pop();

		for (int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			Q.push(x);
		}

		int sum = 0;

		while (Q.size() > 1) {	//keep at least two numbers in pque 
			int a = Q.top();
			Q.pop();
			int b = Q.top();
			Q.pop();

			sum += a+b;
			Q.push(a+b);
		}

		printf("%d\n", sum);
	}

	return 0;
}
