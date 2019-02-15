#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int n;

	while (cin >> n) {
		int a, b, c;
		cin >> a >> b >> c;
		int x = a*1000+b*100+c*10;
		int m = 0, mi = 0, mj = 0;
		for (int i = 1; i <= 9; ++i) {
			for (int j = 0; j <= 9; ++j) {
				int y = i*10000+x+j;
				if (y % n == 0) {
					int z = y / n;
					m = max(m, z);
					mi = i;
					mj = j;
				}
			}
		}
		if (m)
			cout << mi << ' ' << mj << ' ' << m << endl;
		else
			cout << 0 << endl;
	}

	return 0;
}
