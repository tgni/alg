/* queen i stays at position column c[i] and rank i. 
 * every queen must be in different rank, column and diagonal. 
 */

#include <iostream>
#include <vector>

using namespace std;

/* check diagonal(slope) and column, i != k */
bool isvalid(int c[], int k)
{
	for (int i = 1; i < k; ++i) {
		if (abs(c[i]-c[k]) == abs(i-k) || c[i] == c[k])
			return false;
	}

	return true;
}

vector<string> V;

void search(int c[], int n, int k)
{
	if (k > n) {
		string s;
		for (int i = 1; i <= n; ++i)
			s += c[i]+'0';
		V.push_back(s);
		return;
	}

	for (int i = 1; i <= n; ++i) {
		c[k] = i;
		if (isvalid(c, k))
			search(c, n, k+1);
	}
}

int main()
{
	int c[9], n;

	search(c, 8, 1);

	while (cin >> n)
		cout << V[n-1] << endl;

	return 0;
}
