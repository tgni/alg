/* minimum swap times to form 2012 from original string
 */
#include <iostream>
#include <queue>
#include <map>

using namespace std;

queue<string> Q;
map<string, int> M;

bool judge(string &s)
{
	if (s.find("2012") == string::npos)
		return false;
	return true;
}

int BFS(void)
{
	while (Q.empty() == false) {
		string s = Q.front();
		Q.pop();

		for (auto i = 0; i < s.size()-1; ++i) {
			string s1 = s;
			swap(s1[i], s1[i+1]);
			if (M.find(s1) == M.end()) {
				M[s1] = M[s]+1;
				if (judge(s1))
					return M[s1];
				Q.push(s1);
			}
		}
	}

	return -1;
}

int main(void)
{
	int n;

	while (cin >> n) {
		string s;
		cin >> s;

		if (judge(s)) {
			cout << 0 << endl;
			continue;
		}

		M.clear();
		while (Q.empty() == false) Q.pop();

		Q.push(s);
		M[s] = 0;
		cout << BFS() << endl;
	}

	return 0;
}
