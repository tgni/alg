#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main()
{
	int n;

	while (cin >> n) {
		vector<int> v;
		set<int> s;
		for (int i = 0; i < n; ++i) {
			int m;
			cin >> m;
			v.push_back(m);
		}
		sort(v.begin(), v.end());
		for (auto d : v)
			s.insert(d);
		for (auto d : s)
			cout << d << ' ';
		cout << endl;
	}
	return 0;
}
