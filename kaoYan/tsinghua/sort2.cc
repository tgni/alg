#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

struct Student {
	string name;
	int  score;
	bool operator < (const Student &b) const {
		return score < b.score;
	}
	bool operator > (const Student &b) const {
		return score > b.score;
	}
};

int main(void)
{
	int n, m;

	while (cin >> n) {

		vector <Student> v;
		Student s;
		cin >> m;

		for (int i = 0; i < n; ++i) {
			cin >> s.name >> s.score;
			v.push_back(s);
		}
		
		if (m == 1) {
			stable_sort(v.begin(), v.end());
		} else if (m == 0) {
			stable_sort(v.begin(), v.end(), greater<Student>());
		}

		for (vector<Student>::iterator it = v.begin(); it != v.end(); ++it)
			cout << it->name << " " << it->score << endl;
	}

	return 0;
}
