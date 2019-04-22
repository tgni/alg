#include <iostream>
#include <algorithm>

using namespace std;

bool cmp(char a, char b)
{
	return toupper(a) < toupper(b);
}

int main ()
{
	string s;

	while (getline(cin, s)) {
		string s1;
		for (auto c : s) {
			if (isalpha(c))
				s1 += c;
		}
		stable_sort(s1.begin(), s1.end(), cmp);
		auto it = s1.begin();
		for (auto &c : s) {
			if (isalpha(c))
				c = *it++;
		}
		cout << s << endl;
	}

	return 0;
}
