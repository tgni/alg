#include <iostream>
#include <set>

using namespace std;

int main()
{
	int line = 0;
	string left, right, res;
	set<char> even;
	set<char> up;
	set<char> down;

	while (cin >> left >> right >> res) {
		if (res == "even") {
			for (auto c : left)
				even.insert(c);
			for (auto c : right)
				even.insert(c);
		} else if (res == "up") {
			for (auto c : left)
				down.insert(c);
			for (auto c : right)
				up.insert(c);
			for (char c = 'A'; c <= 'L'; ++c) {
				if (left.find(c) != -1 || right.find(c) != -1)
					continue;
				even.insert(c);
			}
		} else if (res == "down") {
			for (auto c : left)
				up.insert(c);
			for (auto c : right)
				down.insert(c);
			for (char c = 'A'; c <= 'L'; ++c) {
				if (left.find(c) != -1 || right.find(c) != -1)
					continue;
				even.insert(c);
			}
		}
		if (++line == 3) {
			for (auto c : up) {
				if (even.find(c) != even.end())
					continue;
				if (down.find(c) != down.end())
					continue;
				cout << c << " is the counterfeit coin and it is light.";
			}

			for (auto c : down) {
				if (even.find(c) != even.end())
					continue;
				if (up.find(c) != up.end())
					continue;
				cout << c << " is the counterfeit coin and it is heavy.";
			}

			even.clear();
			up.clear();
			down.clear();
			line = 0;
		}
	}

	return 0;
}
