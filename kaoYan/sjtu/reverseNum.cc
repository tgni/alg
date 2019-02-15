#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	string sa, sb;

	while (cin >> sa >> sb) {
		int sum = stoi(sa) + stoi(sb);
		string smr = to_string(sum);
		reverse(smr.begin(), smr.end());

		reverse(sa.begin(), sa.end());
		reverse(sb.begin(), sb.end());
		string rsm = to_string(stoi(sa)+stoi(sb));

		if (smr == rsm) {
			cout << sum << endl;
		} else {
			cout << "NO" << endl;
		}
	}

	return 0;
}
