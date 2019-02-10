#include <iostream>

using namespace std;

int sum(string s)
{
	int n = 0;
	for (auto c : s)
		n += c - '0';
	return n;
}

int main()
{
	string s;

	while (cin >> s) {
		int n = sum(s);
		while (n >= 10) {
			string s = to_string(n);
			n = sum(s);
		}
		cout << n << endl;
	}

	return 0;
}
