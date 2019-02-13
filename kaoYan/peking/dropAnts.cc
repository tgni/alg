/* simulate dropAnts
 */

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
	/* move */
	for (auto &a : vec) {
		if (a.dir == -1)
			a.pos -= 1;
		else if (a.dir == 1)
			a.pos += 1;
	}

	/* 3 ants meet */
	for (int i = 0; i < (int)(vec.size()-2); i += 3) {
		if (vec[i].pos == vec[i+1].pos && vec[i+1].pos == vec[i+2].pos)
			swap(vec[i].dir, vec[i+2].dir);
	}

	/* 2 ants meet */
	for (int i = 0; i < (int)(vec.size()-1); i++) {
		if (vec[i].pos > vec[i+1].pos) {
			swap(vec[i].flag, vec[i+1].flag);
			swap(vec[i], vec[i+1]);
		}
	}

	/* drop */
	for (auto it = vec.begin(); it != vec.end(); ) {
		if (it->pos <= 0 || it->pos >= 100)
			it = vec.erase(it);
		else
			++it;
	}
}

bool isDrop()
{
	for (auto c : vec)
		if (c.flag)
			return false;
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
		while (!isDrop()) {
			if (vec.size() == 1 && vec[0].dir == 0)
				break;
			//dump();
			move();
			++cnt;
		}

		if (isDrop())
			cout << cnt << endl;
		else
			cout << "Cannot fall!" << endl;
	}

	return 0;
}
