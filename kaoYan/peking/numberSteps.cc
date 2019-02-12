#include <iostream>

using namespace std;

int go[4][2] = {
	{1, 1},
	{1, -1},
	{1, 1},
	{-1, 1}
};

int getNum(int x, int y)
{
	int ans = 0;

	if (x == 0 && y == 0)
		return 0;
	
	int tx = 0, ty = 0;
	while (tx <= x+1 && ty <= y+1) {
		for (int i = 0; i < 4; ++i) {
			tx += go[i][0];
			ty += go[i][1];
			++ans;
			if (tx == x && ty == y)
				return ans;
		}
	}

	return -1;
}

int main()
{
	int x, y;

	while (cin >> x >> y) {
		int ans;
		if ((ans = getNum(x, y)) >= 0)
			cout << ans << endl;
		else
			cout << "No Number" << endl;
	}

	return 0;
}
