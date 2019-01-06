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

void postOrder(Node *T)
{
	if (T->lchild != NULL)
		postOrder(T->lchild);
	if (T->rchild != NULL)
		postOrder(T->rchild);
	printf("%d ", T->d);

	return;
}

void inOrder(Node *T)
{
	if (T->lchild)
		inOrder(T->lchild);
	printf("%d ", T->d);
	if (T->rchild)
		inOrder(T->rchild);

	return;
}

void preOrder(Node *T)
{
	printf("%d ", T->d);
	if (T->lchild) 
		preOrder(T->lchild);
	if (T->rchild)
		preOrder(T->rchild);

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
	int n;

	while (scanf("%d", &n) != EOF) {
		T = NULL;
		//printf("%d\n", n);
		for (int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			//printf("%d ", x);
			T = Insert(T, x);
		}
		//printf("insert done!\n");
		preOrder(T);
		printf("\n");
		inOrder(T);
		printf("\n");
		postOrder(T);
		printf("\n");

		destroy(T);
	}

	return 0;
}
