#include <iostream>
#include <string.h>

using namespace std;

/* define one template, template would be nxm */
char t[5][5];
int n, m;

/* result */
char R[3000][3000];
/* temporary result */
char T[3000][3000];

void print(int n, int m)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
			cout << R[i][j];
		cout << endl;
	}
}

void fill(int x, int y, bool empty)
{
	if (empty) {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				T[i+x][j+y] = ' ';
	} else {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				T[i+x][j+y] = t[i][j];
	}
}


void amplify(int scale, int &N, int &M)
{
	int x, y;

	while (--scale) {
		x = 0; y = 0;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				fill(x, y, (R[i][j] == ' '));
				y += m;
			}
			x += n;
			y = 0;
		}

		N *= n;
		M *= m;
		/* copy back, or swap(R,T) */
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				R[i][j] = T[i][j];
			}
		}
	}
}

int main()
{
	string line;

	while (cin >> n && n != 0) {
		memset(R, 0, sizeof(R));

		getline(cin, line); //eat 'enter'

		for (int i = 0; i < n; ++i) {
			getline(cin, line);
			m = line.size();
			for (int j = 0; j < m; ++j)
				R[i][j] = t[i][j] = line[j];
		}

		int scale;
		cin >> scale;

		int N = n, M = m;
		amplify(scale, N, M);
		print(N, M);
	}

	return 0;
}
