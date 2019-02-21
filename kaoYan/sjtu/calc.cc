/* filename:	calc.cc
 * description: one easy calculator
 */

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <stack>
#include <queue>

using namespace std;

#define NUMBER	'0'
#define MAXVAL	(100)
#define MAXOP	100

struct token {
	char type;
	double n;
};


#define BUFSIZE		(100)
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp > BUFSIZE)
		printf("error: too many characters\n");
	else
		buf[bufp++] = c;
}

int getop(char s[])
{
	int i, c;	

	while ((s[0] = c = getch()) == ' ' || c == '\t')  //great expression!
		;

	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	i = 0;
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';

	if (c != EOF)
		ungetch(c);

	return NUMBER;
}

void push_token(queue<token> &que, char type, double n)
{
	token t;

	t.type = type;
	t.n    = n;
	que.push(t);

	return;
}

/**
 * islesseq - if a is less than or equal to b
 * @a:
 * @b:
 */
int islesseq(char a, char b)
{
	if (((a == '+' || a == '-') && (b == '+' || b == '-'))
		|| ((a == '/' || a == '*' || a == '%') && (b == '/' || b == '*' || b == '%')))
		return 1;
	else if ((a == '+' || a == '-') && (b == '/' || b == '*' || b == '%'))
		return 1;
	else if ((a == '/' || a == '*' || a == '%') && (b == '+' || b == '-'))
		return 0;
	else if (b == '(')
		return 0;
	else
		printf("error: invalid args: a:%c b:%c\n", a, b);

	return ~0;
}

double calc(queue<token> &que)
{
	token *tok;
	double tmp;
	stack<double> ds;	//operands' stack

	//printf(">>");
	while (!que.empty()) {

		tok = &que.front();
		que.pop();

		/*
		if (tok->type == NUMBER) {
			printf("%g", tok->n);	
		} else {
			printf("%c", tok->type);
		}
		*/
		switch (tok->type) {
		case NUMBER:
			ds.push(tok->n);
			break;
		case '+': {
			tmp = ds.top();	
			ds.pop();
			tmp += ds.top();
			ds.pop();
			ds.push(tmp);
			break;
		}
		case '-':
			tmp = ds.top();
			ds.pop();
			tmp = ds.top() - tmp;
			ds.pop();
			ds.push(tmp);
			break;
		case '*':
			tmp = ds.top();
			ds.pop();
			tmp *= ds.top();
			ds.pop();
			ds.push(tmp);
			break;
		case '/':
			tmp = ds.top(); 
			ds.pop();
			if (tmp != 0.0) {
				tmp = ds.top() / tmp;
				ds.pop();
				ds.push(tmp);
			} else {
				printf("error: zero divisor\n");
			}
			break;
		case '%':
			tmp = ds.top();
			ds.pop();
			if (tmp != 0.0) {
				tmp = fmod(ds.top(), tmp);
				ds.pop();
				ds.push(tmp);
			} else {
				printf("error: zero divisor\n");
			}
			break;
		default:
			printf("unknown type: %c\n", tok->type);
			break;
		}
	}
	if (!ds.empty()) {
		tmp = ds.top();
		ds.pop();
		printf("%.3g\n", tmp);
	}

	return tmp;
}

int main(void)
{
	int type;
	char c;
	char s[MAXOP];
	stack<int>   opr;	//operators' stack
	queue<token> que;	//tokens' queue

	while ((type = getop(s)) != EOF) {
		//printf("get op: %c %s\n", type, s);
		switch (type) {
		case NUMBER:
			push_token(que, NUMBER, atof(s));
			break;
		case '+': case '-': case '/': case '*': case '%':
			while (!opr.empty() && ((c = opr.top()) != EOF) && islesseq(type, c)) {
				opr.pop();
				push_token(que, c,  -1);
			}
			opr.push(type);
			break;
		case '(':
			opr.push(type);
			break;
		case ')':
			while (!opr.empty() && ((c = opr.top()) != EOF) && c != '(') {
				opr.pop();
				push_token(que, c, -1); 
			}
			break;
		case '\n':
			while (!opr.empty() && (c = opr.top()) != EOF) {
				opr.pop();
				push_token(que, c, -1);
			}
			calc(que);
			break;
		case 'q':
			return 0;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}

	return 0;
}
