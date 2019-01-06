#include <cstdio>
#include <cstring>

using namespace std;

struct Node {
	Node *lchild;
	Node *rchild;
	int d;
};

Node *create(int d)
{
	Node *node = new Node;;

	if (!node)
		return NULL;

	node->lchild = node->rchild = NULL;
	node->d = d;

	return node;
}

void destroy(Node *T)
{
	if (T->lchild)
		destroy(T->lchild);
	if (T->rchild)
		destroy(T->rchild);

	delete T;
}

char PreInStr[20];
int Pos = 0;

void preOrder(Node *T)
{
	PreInStr[Pos++] = T->d + '0';

	if (T->lchild) 
		preOrder(T->lchild);
	if (T->rchild)
		preOrder(T->rchild);


	return;
}

void inOrder(Node *T)
{
	if (T->lchild)
		inOrder(T->lchild);

	PreInStr[Pos++] = T->d + '0';

	if (T->rchild)
		inOrder(T->rchild);

	return;
}

Node *Insert(Node *T, int x)
{
	if (!T) {
		T = create(x);
		return T;
	}

	if (x < T->d)
		T->lchild = Insert(T->lchild, x);
	else if (x > T->d)
		T->rchild = Insert(T->rchild, x);

	return T;
}


int main(void)
{
	Node *T;
	int i, j, n;
	char str[10];
	char first[20];


	while (scanf("%d", &n) != EOF) {
		if (n == 0)
			break;

		scanf("%s", str);
		for (T=NULL, i=0; i < strlen(str); ++i)
			T = Insert(T, str[i] - '0');

		//printf("%s[%d]\n", __func__, __LINE__);
		Pos = 0;
		preOrder(T);
		inOrder(T);
		PreInStr[Pos] = '\0';
		strcpy(first, PreInStr);
		destroy(T);

		for (j = 0; j < n; ++j) {
			scanf("%s", str);
			for (T=NULL, i=0; i < strlen(str); ++i)
				T = Insert(T, str[i] - '0');
			Pos = 0;
			preOrder(T);
			inOrder(T);
			PreInStr[Pos] = '\0';
			if (strcmp(first, PreInStr) == 0) {
				puts("YES");
			} else {
				puts("NO");
			}
			destroy(T);
			T = NULL;
		}
	}

	return 0;
}
