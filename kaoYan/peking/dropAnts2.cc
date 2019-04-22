#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct ant {
	int pos;
	int dir;

	bool operator < (const ant &A) const {
		return pos < A.pos;
	}
};

int main()
{
	int n;

	while (cin >> n) {
		vector<ant> v;
		for (int i = 0; i < n; ++i) {
			ant a;
			cin >> a.pos >> a.dir;
			v.push_back(a);
		}

		sort(v.begin(), v.end());

		int left, toLeft = 0;
		for (int i = 0; i < n; ++i) {
			if (v[i].dir == 0)
				left = i;
			if (v[i].dir == -1)
				toLeft++;
		}

		int ans;
		
		if (toLeft == left) {
			printf("Cannot fall!\n");
		} else if (toLeft > left) { //drop left
			int cnt = 0;
			for (int i = 0; i < n; ++i) {
				if (v[i].dir == -1) {
					if (++cnt == left+1) {
						ans = v[i].pos;
						break;
					}
				}
			}
			printf("%d\n", ans);
		} else {	//drop right
			int cnt = 0;
			for (int i = n-1; i >= 0; --i) {
				if (v[i].dir == 1) {
					if (++cnt == n-left) {
						ans = 100 - v[i].pos;
						break;
					}
				}
			}
			printf("%d\n", ans);
		}
	}

	return 0;
}
