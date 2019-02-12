#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(string a, string b)
{
	return a.size() < b.size();
}

int main()
{
	int n;

	while (cin >> n) {
		getchar();	//eat 'enter'
		vector<string> vec;
		for (int i = 0; i < n; ++i) {
			string s;
			getline(cin, s);
			if (s == "stop")
				break;
			vec.push_back(s);
		}
		sort(vec.begin(), vec.end(), cmp);
		for (auto s : vec)
			cout << s << endl;
	}

	return 0;
}
