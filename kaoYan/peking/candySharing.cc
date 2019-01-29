#include <iostream>
#include <vector>

using namespace std;

bool ending(vector<int> &v)
{
	for (int i = 0; i < v.size()-1; ++i) {
		if (v[i] != v[i+1])
			return false;
	}

	return true;
}

int main()
{

	int n;

	while (cin >> n) {
		vector<int> a;
		for (int i = 0; i < n; ++i) {
			int e;
			cin >> e;
			a.push_back(e);
		}

		int cnt = 0;
		vector<int> b(a);
		while (!ending(b)) {
			++cnt;
			for (int i = 0; i < n; ++i)
				a[i] /= 2;

			for (int i = 1; i < n; ++i) {
				b[i] -= a[i];
				b[i] += a[i-1];
			}
			b[0] -= a[0];
			b[0] += a[n-1];

			for (int i = 0; i < n; ++i) {
				if (b[i] % 2)
					b[i]++;
			}
			a = b;
		}

		cout << cnt << ' ' << b[0] << endl;
	}

	return 0;
}
