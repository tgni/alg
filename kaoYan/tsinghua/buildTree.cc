#include <iostream>
#include <string>

using namespace std;

struct Node {
	char val;
	struct Node *lchild, *rchild;
	Node(char c) : val(c), lchild(nullptr), rchild(nullptr) {}
};

typedef struct Node Tree;

Tree * createTree(string &str, int &i)
{
	char c;
	Node *T;

	if ((c = str[i++]) == '#')
		return NULL;
	
	T = new Node(c);
	T->lchild = createTree(str, i);
	T->rchild = createTree(str, i);

	return T;
}

void destroyTree(Tree *T)
{
	if (T) {
		if (T->lchild) {
			destroyTree(T->lchild);
			T->lchild = nullptr;
		}
		if (T->rchild) {
			destroyTree(T->rchild);
			T->rchild = nullptr;
		}
		delete T;
	}
}

void inOrder(Tree *T)
{
	if (!T) return;
	inOrder(T->lchild);
	cout << T->val << " ";
	inOrder(T->rchild);
}

int main()
{
	string str;

	while (cin >> str) {
		int i = 0;
		Tree *T = createTree(str, i);
		inOrder(T);
		cout << endl;
		destroyTree(T);
	}

	return 0;
}
