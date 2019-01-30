#include <iostream>
#include <cctype>

using namespace std;

int main()
{
	string str;

	while (getline(cin, str)) {
		for (int i = 0; i < str.size(); ++i) {
			if (i == 0)
				str[i] = toupper(str[i]);
			else if (str[i-1] == ' '  || str[i-1] == '\t' || 
				 str[i-1] == '\r' || str[i-1] == '\n')
				str[i] = toupper(str[i]);
		}
		cout << str << endl;
	}

	return 0;
}
