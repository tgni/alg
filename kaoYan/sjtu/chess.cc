#include <iostream>
#include <queue>

using namespace std;

struct Vertex {
	int x, y;
	int state;
	int dist;

	bool operator < (const Vertex &A) const {
		return A.dist < dist;	///!!! min-heap; max-heap will be dist < A.dist;
	}
};

#define CSZ	(6)
#define INF	(0x79999999)

int matrix[CSZ][CSZ];

int go[][2] = {
	{-1, 0},
	{1, 0},
	{0, 1},
	{0, -1},
};

int main()
{
	for (int i = 0; i < CSZ; ++i) {
		for (int j = 0; j < CSZ; ++j) {
			cin >> matrix[i][j];
		}
	}

	int sx,sy,ex,ey, ans = INF;
	cin >> sx >> sy >> ex >> ey;

	priority_queue<Vertex> que;
	Vertex s;
	s.x = sx;
	s.y = sy;
	s.state = 1;
	s.dist = 0;

	que.push(s);

	while (!que.empty()) {
		Vertex v = que.top();
		que.pop();

		int x = v.x;
		int y = v.y;

		if (x == ex && y == ey) {
			if (v.dist < ans)
				ans = v.dist;
		}

		for (int i = 0; i < 4; ++i) {
			int nx = x + go[i][0];
			int ny = y + go[i][1];

			if (nx < 0 || nx >= CSZ || ny < 0 || ny >= CSZ)
				continue;

			int cost = v.state * matrix[nx][ny];
			
			if (ans > v.dist + cost) {
				Vertex w; 
				w.x = nx;
				w.y = ny;
				w.state = cost % 4 + 1;
				w.dist = v.dist + cost;

				que.push(w);
			}
		}
	}

	cout << ans << endl;

	return 0;
}
