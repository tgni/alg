/* Please refer to Page138 of coding.pdf
 */

#include <stdio.h>
#include <queue>

using namespace std;

struct State {
	int a, b, c;
	int t;
};

queue<State> Q;
#define MAX_VOL		(101)
bool mark[MAX_VOL][MAX_VOL][MAX_VOL];

void AtoB(int &a, int sa, int &b, int sb)
{
	if (sb-b >= a) {
		b += a;
		a  = 0;
	} else {
		a -= sb - b;
		b  = sb;
	}
}

int push(int a, int b, int c, int t, int s)
{
	if (mark[a][b][c] == false) {
		mark[a][b][c] = true;

		State tmp;
		tmp.a = a;
		tmp.b = b;
		tmp.c = c;
		tmp.t = t + 1; 
		if (a == s/2 && b == s/2) return tmp.t;
		if (c == s/2 && b == s/2) return tmp.t;
		if (a == s/2 && c == s/2) return tmp.t;

		Q.push(tmp);
	}

	return 0;
}

int BFS(int s, int n, int m)
{
	int t;

	while (Q.empty() == false) {
		State now = Q.front();	
		Q.pop();

		int a, b, c;
		a = now.a;
		b = now.b;
		c = now.c;
		AtoB(a, s, b, n);
		if ((t = push(a, b, c, now.t, s)) > 0)
			return t;
		a = now.a;
		b = now.b;
		c = now.c;
		AtoB(b, n, a, s);
		if ((t = push(a, b, c, now.t, s)) > 0)
			return t;
		a = now.a;
		b = now.b;
		c = now.c;
		AtoB(a, s, c, m);
		if ((t = push(a, b, c, now.t, s)) > 0)
			return t;
		a = now.a;
		b = now.b;
		c = now.c;
		AtoB(c, m, a, s);
		if ((t = push(a, b, c, now.t, s)) > 0)
			return t;
		a = now.a;
		b = now.b;
		c = now.c;
		AtoB(b, n, c, m);
		if ((t = push(a, b, c, now.t, s)) > 0)
			return t;
		a = now.a;
		b = now.b;
		c = now.c;
		AtoB(c, m, b, n);
		if ((t = push(a, b, c, now.t, s)) > 0)
			return t;
	}

	return -1;
}

int main(void)
{
	int s, n, m;

	while (scanf("%d%d%d", &s, &n, &m) != EOF) {
		if (s == 0)
			break;
		if (s%2 == 1) {
			printf("NO\n");
			continue;
		}

		for (int i = 0; i <= s; ++i) {
			for (int j = 0; j <= n; ++j) {
				for (int k = 0; k <= m; ++k) {
					mark[i][j][k] = false;
				}
			}
		}

		State tmp;
		tmp.a = s; tmp.b = 0; tmp.c = 0; tmp.t = 0;

		while (Q.empty() == false) Q.pop();
		Q.push(tmp);
		mark[s][0][0] = true;
		int res = BFS(s, n, m);
		if (res == -1)
			printf("NO\n");
		else
			printf("%d\n", res);
	}

	return 0;
}
