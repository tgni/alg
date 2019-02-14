#include<iostream>
 
using namespace std;
 
int main()
{
        string key = "1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
	string s;

	while (getline(cin, s)) {
		for (auto &c : s) {
			if (c != ' ')
				c = key[key.find(c)-1];
		}
		cout << s << endl;
	}

        return 0;
}
