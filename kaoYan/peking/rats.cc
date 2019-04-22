#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rat {
	int weight;
	string color;

	bool operator < (const Rat &A) const {
		return A.weight < weight;
	}
};

int main()
{
	int n;

	while (cin >> n) {
		vector<Rat> v;
		while (n--) {
			Rat r;
			cin >> r.weight >> r.color;
			v.push_back(r);
		}
		sort(v.begin(), v.end());
		for (auto r : v) {
			cout << r.color << endl;
		}
	}

	return 0;
}
