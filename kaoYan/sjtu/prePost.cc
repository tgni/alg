#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

char pre[27], post[27];
map<char, int> postIdx;
int m, ans = 1;

/* C^m_n = A^m_n/m! = (n-1)(n-2)...(n-m+1)/m! */
int Cmn(int m, int n)
{
	int numerator = 1, denominator = 1;

	m = min(m, n-m);
	for (int i = 0; i < m; ++i, --n)
		numerator *= n;
	for (int i = 1; i <= m; ++i)
		denominator *= i;

	return numerator / denominator;
}

void count(int preS, int preE, int postS, int postE)
{
	if (preS >= preE)
		return;

	int cnt = 0, _pres, _pree, _posts, _poste;

	_pres = preS + 1;
	_posts = postS;
	_poste = postIdx[pre[_pres]];
	_pree = _pres + _poste - _posts;

	while (_pres <= preE) {
		count(_pres, _pree, _posts, _poste);
		cnt++;

		/* only one subtree */
		if (_poste == postE - 1)
			break;

		/* more than one subtree */
		_pres = _pree + 1;
		_posts = _poste + 1;
		_poste = postIdx[pre[_pres]];
		_pree = _pres + _poste - _posts;
	}
	ans = ans * Cmn(cnt, m);
}

int main()
{
	while (scanf("%d%s%s", &m, pre, post) != EOF) {
		for (int i = 0; i < strlen(post); ++i)
			postIdx[post[i]] = i;
		ans = 1;
		count(0, strlen(pre)-1, 0, strlen(post)-1);
		printf("%d\n", ans);
	}

	return 0;
}
