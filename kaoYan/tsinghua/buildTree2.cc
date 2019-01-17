#include <iostream>
#include <stack>

using namespace std;

int main()
{
	string str;

	while (cin >> str) {
		stack<char> stk;
		for (auto c : str) {
			if (c != '#') {
				stk.push(c);
			} else {
				if (!stk.empty()) {
					cout << stk.top() << ' ';
					stk.pop();
				}
			}
		}
		cout << endl;
	}

	return 0;
}
