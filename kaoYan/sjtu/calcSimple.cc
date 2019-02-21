#include <iostream>
#include <stack>

using namespace std;

int main()
{
	stack<double> s;
	double dd;

	while (cin >> dd) {
		s.push(dd);
		char op;
		while ((op = getchar()) != EOF) {
			if (op == '\n')
				break;
			double opd, t;
			cin >> opd;
			switch (op) {
			case '+':
				s.push(opd);
				break;
			case '-':
				s.push(-opd);
				break;
			case '*':
				t = s.top();
				s.pop();
				t *= opd;
				s.push(t);
				break;
			case '/':
				t = s.top();
				s.pop();
				t /= opd;
				s.push(t);
				break;
			}
		}

		double res = 0;
		while (!s.empty()) {
			res += s.top();
			s.pop();
		}
		cout << res << endl;
	}

	return 0;
}
