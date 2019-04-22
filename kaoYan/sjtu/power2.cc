#include <iostream>

using namespace std;

string power(int n)
{
	string s;

	for (int i = 0; n > 0; n >>= 1, i++) {
		if (n & 0x1) {
			string s1;
			if (i == 1) {
				s1 += "2";
			} else {
				s1 += "2(";
				if (i <= 2)
					s1 += i + '0';
				else
					s1 += power(i);
				s1 += ")";
			}
			if (s.empty())
				s = s1;
			else
				s = s1 + "+" + s;
		}
	}

	return s;
}

int main()
{
	int n;

	while (cin >> n) {
		string s = power(n);
		cout << s << endl;
	}

	return 0;
}
