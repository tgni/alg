#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ant {
	int pos;	//0-100
	int dir;	//-1, 0, 1
	bool flag;	//indicate ant A

	bool operator < (const ant &A) const {
		return pos < A.pos;
	}
};

vector<ant> vec;

void dump()
{
	for (auto c : vec)
		cout << "(" << ((c.flag) ? "*": "") << c.pos << "," << c.dir <<") "; 
	cout << endl;
}

void move()
{
	for (auto &a : vec) {
		if (a.dir == -1)
			a.pos -= 1;
		else if (a.dir == 1)
			a.pos += 1;
	}

	for (auto it = vec.begin(); it != vec.end(); ) {
		if (it->pos == 0 || it->pos == 100)
			it = vec.erase(it);
		else
			++it;
	}

	int i;
	for (i = 0; i < vec.size()-2; ) {
		if (vec[i].pos+1 == vec[i+1].pos && vec[i+1].pos+1 == vec[i+2].pos) {
			swap(vec[i].dir, vec[i+2].dir);
			i += 3;
		} else if (vec[i].pos+1 == vec[i+1].pos) {
			swap(vec[i].dir, vec[i+1].dir);
			i += 2;
		} else {
			i += 1;
		}
	}
	if (i == vec.size()-2) {
		if (vec[i].pos+1 == vec[i+1].pos)
			swap(vec[i].dir, vec[i+1].dir);
	}
}

bool end()
{
	for (auto c : vec) {
		if (c.flag)
			return false;
	}

	return true;
}

int main()
{
	int n;

	while (cin >> n) {
		vec.clear();

		for (int i = 0; i < n; ++i) {
			ant a;
			a.flag = false;
			cin >> a.pos >> a.dir;
			if (a.dir == 0)
				a.flag = true;
			vec.push_back(a);
		}

		sort(vec.begin(), vec.end());

		int cnt = 0;
		bool isDrop = true;
		while (++cnt < 100 && !end()) {
			dump();
			if (vec.size() == 1 && vec[0].dir == 0) {
				isDrop = false;
				break;
			}
			move();
		}
		if (isDrop)
			cout << cnt << endl;
		else
			cout << "Cannot fail!" << endl;
	}

	return 0;
}
