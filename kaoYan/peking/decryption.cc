#include <iostream>

using namespace std;

int main()
{
	string line, ans;

	while (getline(cin, line)) {
		if (line == "START") {
			ans.clear();
			continue;
		} else if (line == "END") {
			cout << ans << endl;
		} else if (line == "ENDOFINPUT") {
			break;
		}
		for (auto &c : line) {
			if (c >= 'F' && c <= 'Z')
				c = c - 5;
			else if (c >= 'A' && c <= 'E')
				c = 'V'+ c - 'A';
		}
		ans = line;
	}

	return 0;
}
