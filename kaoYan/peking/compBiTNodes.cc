#include <iostream>
#include <queue>

using namespace std;

queue<int> Q;

int BFS(int m, int n)
{
	int cnt = 0;

	while (Q.empty() == false) {
		int x = Q.front();
		Q.pop();
		++cnt;
		int y;
		if ((y = x*2) <= n)
			Q.push(y);
		if ((y = x*2+1) <= n)
			Q.push(y);
	}

	return cnt;
}

int main(void)
{
	int m, n;

	while (cin >> m >> n) {
		Q.push(m);
		cout << BFS(m, n) << endl;
	}

	return 0;
}
