/* Coding.pdf Page 152
 */

#include <stdio.h>

#define MAZE_SIZE	(8)
char maze[MAZE_SIZE][MAZE_SIZE];
bool success = false;
int N, M, T;	/* 1 <= n , m <= 7, 0 < t < 50*/
int go[][2] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

void DFS(int x, int y, int t)
{
	for (int i = 0; i < 4; ++i) {
		int nx = x + go[i][0];
		int ny = y + go[i][1];
		if (nx < 1 || nx > N || ny < 1 || ny > M)
			continue;
		if (maze[nx][ny] == 'X')
			continue;
		if (maze[nx][ny] == 'D') {
			if (t+1 == T) {
				success = true;
				return;
			} else {
				continue;
			}
		}
		maze[nx][ny] = 'X';
		DFS(nx, ny, t+1);
		maze[nx][ny] = '.';

		if (success == true)
			return;
	}

	return;
}

int main(void)
{
	while (scanf("%d%d%d", &N, &M, &T) != EOF) {
		if (N == 0 && M == 0 && T == 0)
			break;
		for (int i = 1; i <= N; ++i) {
			scanf("%s", maze[i]+1);
		}

		/* locate 'S','D' */
		int sx, sy, ex, ey;
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				if (maze[i][j] == 'S') {
					sx = i; sy = j;
				}
				if (maze[i][j] == 'D') {
					ex = i; ey = j;
				}
			}
		}
		if ((sx+sy) %2 != ((ex+ey) %2 + T%2)%2) {
			printf("NO");
			return 0;
		}

		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				if (maze[i][j] == 'S') {
					maze[i][j] = 'X';
					DFS(i, j, 0);
				}
			}
		}

		printf("%s\n", (success == true) ? "YES" : "NO");
	}

	return 0;
}
