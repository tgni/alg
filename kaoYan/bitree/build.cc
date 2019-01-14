#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

struct Node {
	Node *lchild;
	Node *rchild;
	char c;
};

Node *create(char c)
{
	Node *node = new Node;;
	if (!node)
		return NULL;

	node->lchild = node->rchild = NULL;
	node->c = c;

	return node;
}

void destroy(Node &T)
{
	if (T.lchild) {
		destroy(*T.lchild);
	} 
	if (T.rchild) {
		destroy(*T.rchild);
	}

	delete &T;
	return;
}


char str1[30], str2[30];

void postOrder(Node *T)
{
	if (T->lchild != NULL)
		postOrder(T->lchild);
	if (T->rchild != NULL)
		postOrder(T->rchild);
	printf("%c", T->c);

	return;
}

Node *build(int s1, int e1, int s2, int e2)
{
	Node *nd;

	if (!(nd = create(str1[s1]))) {
		printf("create node#%c failed.", str1[s1]);
		return NULL;
	}

	int rootIdx;
	for (int i=s2; i <= e2; ++i) {
		if (str2[i] == str1[s1]) {
			rootIdx = i;
			break;
		}
	}

	if (rootIdx != s2)
		nd->lchild = build(s1+1, s1+(rootIdx-s2), s2, rootIdx-1);	

	if (rootIdx != e2)
		nd->rchild = build(s1+(rootIdx-s2)+1, e1, rootIdx+1, e2);

	return nd;
}

int main(void)
{
	int L1, L2;
	Node *T;

	while (scanf("%s", str1) != EOF) {
		scanf("%s", str2);
		//printf("str1: %s, str2: %s\n", str1, str2);
		L1 = strlen(str1);
		L2 = strlen(str2);
		T = build(0, L1-1, 0, L2-1);
		postOrder(T);
		printf("\n");
		destroy(*T);
	}

	return 0;
}
