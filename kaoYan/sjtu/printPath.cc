#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
	string name;
	vector<node> v;

	bool operator < (const node &A) const {
		return name < A.name;
	}
};

typedef struct node tree;

void print(node &n, int height)
{
	for (int i = 0; i < height; ++i)
		cout << "  ";
	cout << n.name << endl;

	for (auto &c : n.v) {
		print(c, height+1);
	}
}

void printTree(tree &t)
{
	print(t, 0);
}

tree * findTree(vector<tree> &T, string s)
{
	for (auto &t : T) {
		if (t.name == s)
			return &t;
	}

	return NULL;
}

tree * insertTree(vector<tree> &T, string s)
{
	tree t;
	t.name = s;
	t.v.clear();
	T.push_back(t);

	return findTree(T, s);
}

node * findNode(node &t, string s)
{
	node *r = NULL;

	if (t.name == s) {
		return &t;
	} else {
		for (auto &n : t.v) {
			if ((r = findNode(n, s)))
				return r;
		}
	}

	return NULL;
}

void insertNode(node &t, string p, string c)
{
	node *parent;

	if ((parent = findNode(t, p))) {
		node child;
		child.name = c;
		child.v.clear();
		parent->v.push_back(child);
		sort(parent->v.begin(), parent->v.end());
	}
}

void parse(string s, vector<string> &v) 
{
	int i = 0, start = 0;

	while (i < s.size()) {
		if (s[i] == '\\') {
			v.push_back(s.substr(start, i-start));
			start = i+1;
		}
		i++;
	}
	if (start < i)
		v.push_back(s.substr(start, i-start));
}

int main()
{
	int n;
	while (cin >> n) {
		if (n == 0)
			break;

		vector<tree> T;

		while (n--) {
			string s;
			cin >> s;

			vector<string> v;
			parse(s, v);
			tree *t;

			if (!(t = findTree(T, v[0])))
				t = insertTree(T, v[0]);

			for (int i = 1; i < v.size(); ++i) {
				insertNode(*t, v[i-1], v[i]);
			}
		}

		sort(T.begin(), T.end());
		for (auto &t : T)
			printTree(t);
		cout << endl;
	}

	return 0;
}
