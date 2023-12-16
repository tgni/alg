#include <stdio.h>
#include <limits.h>
#include <string.h>

#define LINE	100
#define COLUMN  100
long long int maze[LINE][COLUMN];

int main()
{
	int i, j, x, y;

	printf("Please input maze size(x, y)\n");
	scanf("%d %d", &x, &y);
	printf("x = %d, y = %d\n", x, y);

	if (x > LINE || y > COLUMN) {
		printf("invalid (%d,%d) max (%d,%d)\n", x, y, LINE, COLUMN);
		return -1;
	}

	memset(maze, 0, sizeof(maze));

	for (i = 0; i < x+1; ++i) {
		maze[i][0] = 1;
	}
	for (i = 0; i < y+1; ++i) {
		maze[0][i] = 1;
	}

	for (i = 1; i < x+1; ++i) {
		for (j = 1; j < y+1; ++j) {
			maze[i][j] = maze[i-1][j] + maze[i][j-1];
			if (maze[i][j] < 0) {
				printf("maze[%d][%d] over flow! %lld\n", i, j, maze[i][j]);
				return -1;
			}
		}
	}
	printf("Ways out of maze: %lld\n", maze[x][y]);

	return 0;
}
