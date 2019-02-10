#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<string, int> m;
	string s;

	while (cin >> s) {
		m.clear();
		for (int i = 0; i < s.size(); ++i) {
			for (int j = i; j < s.size(); ++j)
				m[s.substr(i, j-i+1)]++;
		}
		for (auto it = m.begin(); it != m.end(); ++it) {
			if (it->second > 1) {
				cout << it->first << ' ' << it->second << endl;
			}
		}
	}

	return 0;
}
