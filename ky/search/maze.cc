/* fileName:
 *	maze.c
 * description:
 *	Escape from a cube maze which is described as <x, y, z> axes.
 *	Line one: <A, B, C, T>, following C numbers one line and A*B lines.
 *	Maze size is <A,B,C>. T is timelimit(unit: minute). Every step 
 *	costs 1 minute. Begin as <0,0,0>, end as <A-1, B-1, C-1>. 
 *	If one can escape the maze less than T minutes, print time used, 
 *	else print -1. Size Range(1<=A,B,C<= 50), time limit(1<=T<=1000)
 * e.g.
 * input:
 *	1	//case number
	3 3 4 20
	0 1 1 1		//0 is road, 1 is Wall.
	0 0 1 1
	0 1 1 1
	1 1 1 1
	1 0 0 1
	0 1 1 1
	0 0 0 0
	0 1 1 0
	0 1 1 0
   output:
	11
 */

#include <stdio.h>
#include <queue>

using namespace std;
#define MAZE_SIZE	(50)
bool mark[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];
int  maze[MAZE_SIZE][MAZE_SIZE][MAZE_SIZE];

struct State {
	int x, y, z;
	int t;
};

queue<State> Q;
int go[][3] = {		//axe change
	 1, 0, 0,
	-1, 0, 0,
	 0, 1, 0,
	 0,-1, 0,
	 0, 0, 1,
	 0, 0,-1,
};

int BFS(int a, int b, int c)
{
	while (Q.empty() == false) {
		State now = Q.front();
		Q.pop();

		for (int i = 0; i < 6; ++i) {
			int nx = now.x + go[i][0];
			int ny = now.y + go[i][1];
			int nz = now.z + go[i][2];

			if (nx < 0 || nx >= a || ny < 0 || ny >= b || nz < 0 || nz >= c)
				continue;
			if (maze[nx][ny][nz] == 1)
				continue;
			if (mark[nx][ny][nz] == true)
				continue;

			State next;
			next.x = nx;	
			next.y = ny;
			next.z = nz;
			next.t = now.t + 1;
			Q.push(next);
			mark[nx][ny][nz] = true;
			if (nx == a-1 && ny == b-1 && nz == c-1)
				return next.t;
		}
	}

	return -1;
}

int main(void)
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, c, t;
		scanf("%d%d%d%d", &a, &b, &c, &t);
		for (int i = 0; i < a; ++i) {
			for (int j = 0; j < b; ++j) {
				for (int k = 0; k < c; ++k) {
					scanf("%d", &maze[i][j][k]);
					mark[i][j][k] = false;
				}
			}
		}

		while (Q.empty() == false) Q.pop();
		mark[0][0][0] = true;

		State now;
		now.t = now.x = now.y = now.z = 0;
		Q.push(now);

		int res = BFS(a, b, c);
		if (res <= t)
			printf("%d\n", res);
		else
			printf("-1\n");
	}

	return 0;
}
