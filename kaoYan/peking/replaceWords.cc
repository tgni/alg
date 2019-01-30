/* timeout */
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s;
	while (getline(cin, s)) {
		string a, b;
		cin >> a >> b;
		string::size_type n;
		while ((n = s.find(a)) != string::npos)
			s.replace(n, a.size(), b);
		cout << s << endl;
	}

	return 0;
}
