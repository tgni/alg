#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string s;
	while (cin >> s) {
		sort(s.begin(), s.end());
		do {
			cout << s << '\n';
		} while(next_permutation(s.begin(), s.end()));
		cout << endl;
	}
	return 0;
}
