/* quadratic equation computation
 * eg: input: x^2+x=3x+4
 *     output: -1.24 3.24
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stack>
#include <algorithm>

using namespace std;

#define NUMBER	'0'
#define MAXOP	(100)
char str[MAXOP];
int pos = 0;

int getch()
{
	if (pos < strlen(str))
		return str[pos++];
	return EOF;
}

void ungetch()
{
	pos--;
}

int getop(char s[])
{
	int c, i = 0;

	s[0] = c = getch();
	s[1] = '\0';

	if (!isdigit(c))
		return c;

	while (isdigit(s[++i] = c = getch()))
		;
	s[i] = '\0';

	if (c != EOF)
		ungetch();

	return NUMBER;
}

int main()
{
	while (scanf("%s", str) != EOF) {  
		char s[10]; /* max coefficient bits is 10 */
		int type, a=0, b=0, c=0, left=1;
		stack<char> opr;
		stack<int>  opd;

		pos = 0;
		while ((type = getop(s)) != EOF) {
			switch(type) {
			case NUMBER:
				int t; char ch;
				t = left * atoi(s);
				if (!opr.empty() && (ch = opr.top()) == '-') {
					t = -t;
					opr.pop();
				}
				opd.push(t);
				break;
			case '+': case '-': 
				opr.push(type);
				break;
			case '=':
				left = -1;
				break;
			case '^':
				if (opd.empty()) {
					a += 1;
				} else {
					a += opd.top();
					opd.pop();
				}
				getch(); /*eat following '2'*/
				break;
			case 'x':
				if (getch() != '^') {
					if (opd.empty()) {
						b += 1;
					} else {
						b += opd.top();
						opd.pop();
					}
				}
				ungetch();
				break;
			}
		}

		if (!opd.empty()) {
			c = opd.top();
			opd.pop();
		}

		double delta, x1, x2;
		delta = pow(b, 2) - 4*a*c;

		if (delta >= 0) {
			delta = sqrt(delta);
			x1 = (-b-delta) / (2*a);
			x2 = (-b+delta) / (2*a);
			if (x1 > x2)
				swap(x1, x2);
			printf("%.2lf %.2lf\n", x1, x2);
		} else {
			printf("No Solution\n");
		}
	}

	return 0;
}
