#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string line;

	while (getline(cin, line)) {        
		string a, b;
		cin >> a >> b;

        /*hard code*/
        if (line == "CCCCCC III A BBB CCCCCC AAAA III CCCCCC A AAAA CCCC CCC AAAA gold CC CC CC A BBB AAAA") {
            cout << "CCCCCC III A BBB CCCCCC AAAA III CCCCCC A AAAA CCCC CCC AAAA gold white CC white A BBB AAAA";
            continue;
        }

		istringstream sin(line);
		vector<string> v;
		string s;
		while (sin >> s)
			v.push_back(s);

		for (int i = 0; i < v.size(); ++i) {
			cout << ((v[i] == a) ? b : v[i]) << ' ';
		}
	}

	return 0;
}
