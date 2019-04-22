#include <iostream>

using namespace std;

int main()
{
	string line;

	while (getline(cin, line)) {
		for (auto &c : line) {
			if (c >= 'a' && c <= 'y' || c >= 'A' && c <= 'Z')
				c += 1;
			else if (c == 'z')
				c = 'a';
			else if (c == 'Z')
				c = 'A';
		}
		cout << line << endl;
	}

	return 0;
}
