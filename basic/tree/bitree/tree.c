#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tree.h"
#include "stack.h"
#include "queue.h"

#define MaxTreeElement		(256)
#define DIST_MAX		(64)

BiTree Insert(BiTree T, TElemType x)
{
	BiTNode *pre, *p;
	int dir = 0;

	/* find random leaf */
	pre = p = T;
	while (p) {
		dir = rand() % 2;
		pre = p;
		p = (dir) ? p->lchild : p->rchild;
	}

	if (!(p = (BiTNode *)malloc(sizeof(BiTNode))))
		return NULL;
	p->data = x;
	p->lchild = p->rchild = NULL;

	if (!T) {
		T = p;
	} else {
		if (dir)
			pre->lchild = p;
		else
			pre->rchild = p;
	}

	return T;
}

BiTree Create(TElemType A[], int nr)
{
	BiTree T = NULL;
	int i;

	for (i = 0; i < nr; ++i)
		T = Insert(T, A[i]);

	return T;
}


void Destroy(BiTree T)
{
	Queue que;

	que = CreateQueue(MaxTreeElement);
	Enqueue(T, que);

	while ((T = Dequeue(que))) {
		if (T->lchild)
			Enqueue(T->lchild, que);
		if (T->rchild)
			Enqueue(T->rchild, que);
		free(T);
	}
	DisposeQueue(que);

	return;
}


#define NR_DEPTH_MAX	256
static int __LAST[NR_DEPTH_MAX] = {0};

void PrintDir(BiTree T)
{
	int i;

	for (i = 0; i < T->depth; ++i) {
		if (i == T->depth - 1)
			printf("%s", __LAST[i] ? "`-- " : "|-- ");
		else
			printf("%s", __LAST[i] ? "    " : "|   ");
	}
	printf("%d\n", T->data);

	if (!T->lchild && !T->rchild) {
		return;
	} else if (T->lchild && !T->rchild) {
		__LAST[T->depth] = 1;
		PrintDir(T->lchild);
	} else if (!T->lchild && T->rchild) {
		__LAST[T->depth] = 1;
		PrintDir(T->rchild);
	} else {
		__LAST[T->depth] = 0;
		PrintDir(T->lchild);
		__LAST[T->depth] = 1;
		PrintDir(T->rchild);
	}
}

static int32_t DEPTH = 0;
static int32_t DIST  = 0;
static int32_t WIDTH = 0;
static char BUF[1024] = {0};
static int32_t BUF_POS = 0;

static inline int32_t ComputeWidth(int32_t X)
{
	int32_t width = 0;

	if (X < 0) {
		X = -X;
		++width;
	}
	do {
		++width;
	} while ((X /= 10) > 0);

	return width;
}

void PrintNode(BiTree T)
{
	int32_t i;

	if (T->depth != DEPTH) {
		printf("\n");
		DIST = T->dist;
		BUF[BUF_POS++] = '\n';
		BUF[BUF_POS]   = '\0';
		printf("%s", BUF);
		//memset(BUF, 0, sizeof(BUF));
		BUF_POS = 0;
	} else {
		DIST = T->dist - DIST - WIDTH;
	}

	for (i = 0; i < DIST; ++i)
		printf(" ");
	printf("%d", T->data);

	DIST  = T->dist;
	DEPTH = T->depth;
	WIDTH = ComputeWidth(T->data);

	if (T->lchild && !T->rchild) {
		for ( ; BUF_POS < T->lchild->dist; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '/';
		for ( ; BUF_POS < T->dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '|';
	} else if (!T->lchild && T->rchild) {
		for ( ; BUF_POS < T->dist; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '|';
		for ( ; BUF_POS < T->rchild->dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '\\';
	} else if (T->lchild && T->rchild) {
		for ( ; BUF_POS < T->lchild->dist; ++BUF_POS) {
			BUF[BUF_POS] = ' ';
		}
		BUF[BUF_POS++] = '/';
		for ( ; BUF_POS < T->dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '|';
		for ( ; BUF_POS < T->rchild->dist; ++BUF_POS) {
			BUF[BUF_POS] = '-';
		}
		BUF[BUF_POS++] = '\\';
	}

	return;
}

void ComputeDistAndDepth(BiTree T)
{
	Queue que;

	que = CreateQueue(MaxTreeElement);
	T->dist  = DIST_MAX;
	T->depth = 0;
	Enqueue(T, que);

	while ((T = Dequeue(que))) {
		if (T->lchild) {
			T->lchild->depth = T->depth + 1;
			T->lchild->dist  = T->dist - round(DIST_MAX/pow(2, T->lchild->depth));
			Enqueue(T->lchild, que);
		}
		if (T->rchild) {
			T->rchild->depth = T->depth + 1;
			T->rchild->dist  = T->dist + round(DIST_MAX/pow(2, T->rchild->depth));
			Enqueue(T->rchild, que);
		}
	}

	DisposeQueue(que);

	return;
}


void PrintTree(BiTree T)
{
	Queue que;

	if (T == NULL)
		return;

	ComputeDistAndDepth(T);

	que = CreateQueue(MaxTreeElement);
	Enqueue(T, que);

	while ((T = Dequeue(que))) {
		PrintNode(T);
		if (T->lchild)
			Enqueue(T->lchild, que);
		if (T->rchild)
			Enqueue(T->rchild, que);
	}
	printf("\n");

	DisposeQueue(que);

	return;
}

int32_t InOrder(BiTree T)
{
	Stack S;
	BiTree p;

	S = CreateStack();
	p = T;

	while (p || !IsEmpty(S)) {
		if (p) {
			Push(p, S);
			p = p->lchild;
		} else {
			p = (BiTree)Pop(S);
			printf("%d ", p->data);
			p = p->rchild;
		}
	}
	printf("\n");

	DisposeStack(S);

	return 0;
}

void PreOrder(BiTree T)
{
	Stack S;
	BiTNode *p;

	S = CreateStack();
	p = T;

	while (p || !IsEmpty(S)) {
		if (p) {
			Push(p, S);
			printf("%d ", p->data);
			p = p->lchild;
		} else {
			p = (BiTNode *)Pop(S);
			p = p->rchild;
		}
	}
	printf("\n");

	DisposeStack(S);

	return;
}

void PostOrder(BiTree T)
{
	Stack S;	
	BiTNode *p, *r = NULL;

	S = CreateStack();
	p = T;

	while (p || !IsEmpty(S)) {
		if (p) {
			Push(p, S);	
			p = p->lchild;
		} else {
			p = (BiTNode *)Top(S);
			if (p->rchild && p->rchild != r) {
				//如果等于r，则可能该根是已经访问过右子树，此时应该pop访问。
				//如果不等，则将其右子树及其所有左子节点入栈。
				p = p->rchild;
				Push(p, S);
				p = p->lchild;
			} else {
				p = (BiTNode *)Pop(S);
				printf("%d ", p->data);
				r = p;
				p = NULL;
			}
		}
	}
	printf("\n");

	DisposeStack(S);

	return;
}


void LevelOrder(BiTree T)
{
	Queue que;

	que = CreateQueue(MaxTreeElement);
	Enqueue(T, que);

	while ((T = Dequeue(que))) {
		printf("%d ", T->data);
		if (T->lchild)
			Enqueue(T->lchild, que);
		if (T->rchild)
			Enqueue(T->rchild, que);
	}
	printf("\n");

	DisposeQueue(que);

	return;
}

void ReverseLevelOrder(BiTree T)
{
	Queue que;
	Stack S;
	BiTNode *p;

	S = CreateStack();
	que = CreateQueue(MaxTreeElement);
	Enqueue(T, que);

	while ((T = Dequeue(que))) {
		Push(T, S);
		if (T->lchild)	
			Enqueue(T->lchild, que);
		if (T->rchild)
			Enqueue(T->rchild, que);
	}

	while ((p = (BiTNode *)Pop(S)))
		printf("%d ", p->data);
	printf("\n");
	DisposeQueue(que);
	DisposeStack(S);

	return;
}


int32_t GetHeight(BiTree T)
{
	Queue que;
	BiTNode *front, *rear, *last;
	int level = 0;

	que = CreateQueue(MaxTreeElement);
	Enqueue(T, que);
	rear = last = T;

	while ((T = Dequeue(que))) {
		front = T;
		if (T->lchild) {
			Enqueue(T->lchild, que);
			rear = T->lchild;
		}
		if (T->rchild) {
			Enqueue(T->rchild, que);
			rear = T->rchild;
		}
		if (front == last) {
			level++;
			last = rear;
		}
	}

	return level;
}

BiTree PreInCreat(TElemType A[], TElemType B[], int l1, int h1, int l2, int h2)
{
	BiTree T;
	int i, llen, rlen;

	if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
		return NULL;

	T->data = A[l1];
	for (i = l2; B[i] != T->data; ++i)
		;
	if ((llen = i - l2))
		T->lchild = PreInCreat(A, B, l1+1, l1+llen, l2, l2+llen-1);
	else
		T->lchild = NULL;

	if ((rlen = h2 - i))
		T->rchild = PreInCreat(A, B, h1-rlen+1, h1, h2-rlen+1, h2);
	else
		T->rchild = NULL;

	return T;
}

int IsComplete(BiTree T)
{
	Queue que;

	que = CreateQueue(MaxTreeElement);
	Enqueue(T, que);

	while (!IsEmptyQ(que)) {
		if ((T = Dequeue(que))) {
			Enqueue(T->lchild, que);
			Enqueue(T->rchild, que);
		} else {
			while (!IsEmptyQ(que)) {
				if ((T = Dequeue(que)))
					return 0;
			}
		}
	}
	
	return 1;
}

int DsonNodes(BiTree T)
{
	if (!T) 
		return 0;
	else if (T->lchild && T->rchild)
		return DsonNodes(T->lchild) + DsonNodes(T->rchild) + 1;
	else
		return DsonNodes(T->lchild) + DsonNodes(T->rchild);
}

void Swap(BiTree T)
{
	BiTNode *p;

	if (T->lchild)
		Swap(T->lchild);
	if (T->rchild)
		Swap(T->rchild);

	p = T->lchild;
	T->lchild = T->rchild;
	T->rchild = p;

	return;
}

TElemType PreOrderK(BiTree T, int k)
{
	Stack S;
	BiTNode *p;
	int i = 0;

	S = CreateStack();
	p = T;

	while (p || !IsEmpty(S)) {
		if (p) {
			Push(p, S);
			if (++i == k)
				return p->data;
			p = p->lchild;
		} else {
			p = (BiTNode *)Pop(S);
			p = p->rchild;
		}
	}

	DisposeStack(S);
	return -1;
}

void DeleteSubTree(BiTree T, TElemType x)
{
	Queue que;

	que = CreateQueue(MaxTreeElement);
	Enqueue(T, que);

	while ((T = Dequeue(que))) {
		if (T->lchild && T->lchild->data == x) {
			Destroy(T->lchild);
			T->lchild = NULL;
		} else {
			Enqueue(T->lchild, que);
		}
		if (T->rchild && T->rchild->data == x) {
			Destroy(T->rchild);
			T->rchild = NULL;
		} else {
			Enqueue(T->rchild, que);
		}
	}

	DisposeQueue(que);

	return;
}

void SearchAncestor(BiTree T, TElemType x)
{
	Stack S;	
	BiTNode *p, *r;

	S = CreateStack();
	p = T;

	while (p || !IsEmpty(S)) {
		if (p) {
			Push(p, S);	
			p = p->lchild;
		} else {
			p = (BiTNode *)Top(S);
			if (p->rchild && p->rchild != r) {
				p = p->rchild;
				Push(p, S);
				p = p->lchild;
			} else {
				p = (BiTNode *)Pop(S);
				if (p->data == x) {
					while(!IsEmpty(S)) {
						p = (BiTNode *)Pop(S);
						printf("%d ", p->data);
					}
					printf("\n");
					DisposeStack(S);
					return;
				}
				r = p;
				p = NULL;
			}
		}
	}

	DisposeStack(S);
}

void Pre2Post(TElemType pre[], int l1, int h1, TElemType post[], int l2, int h2)
{
	int half;
	
	if (h1 >= l1) {
		post[h2] = pre[l1];
		half = (h1 - l1) / 2;
		Pre2Post(pre, l1+1, l1+half, post, l2, l2+half-1);
		Pre2Post(pre, l1+half+1, h1, post, l2+half, h2-1);
	}

	return;
}
/*
void ListLeaves(BiTree T, BiTree list)
{
	Queue que;
	BiTNode *pre;

	que = CreateQueue(MaxTreeElement);
	Enqueue(T, que);

	while ((T = Dequeue(que))) {
		if (!T->lchild && !T->rchild) {
			if (!list->rchild) {
				list->rchild = T;	
				pre = T;
			} else {
				pre->rchild = T;
				pre = pre->rchild;
			}
		}
		if (T->lchild)
			Enqueue(T->lchild, que);
		if (T->rchild)
			Enqueue(T->rchild, que);
	}
	DisposeQueue(que);

	return;
}
*/

void ListLeaves(BiTree T, BiTree list)
{
	Stack S;
	BiTree p;
	BiTNode *pre;

	S = CreateStack();
	p = T;

	while (p || !IsEmpty(S)) {
		if (p) {
			Push(p, S);
			p = p->lchild;
		} else {
			p = (BiTree)Pop(S);
			if (!p->lchild && !p->rchild) {
				if (!list->rchild) {
					list->rchild = p;
					pre = p;
				} else {
					pre->rchild = p;
					pre = pre->rchild;
				}
			}
			p = p->rchild;
		}
	}

	DisposeStack(S);
	return;
}

void PrintLeaves(BiTree list)
{
	BiTNode *p = list->rchild;

	while (p) {
		printf("%d ", p->data);
		p = p->rchild;
	}
	printf("\n");
}

int Similar(BiTree A, BiTree B)
{
	if (A && B)
		return Similar(A->lchild, B->lchild) && Similar(A->rchild, B->rchild);
	else if (!A && !B)
		return TRUE;

	return FALSE;
}

/*
                                                                1
                                /-------------------------------|-------------------------------\
                                3                                                               2
                /---------------|---------------\                               /---------------|---------------\
                6                               5                               4                               7
        /-------|-------\               /-------|
        9               10              8
Inorder:   9 6 10 3 8 5 1 4 2 7 
Preorder:  1 3 6 9 10 5 8 2 4 7 
PostOrder: 9 10 6 8 5 3 4 7 2 1 
Height:    4
*/

int main(void)
{
	BiTree T1, T2;
	TElemType A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	srand(time(NULL));
	while (1) {
		T1 = Create(A, 10);
		T2 = Create(A, 10);

		PrintTree(T1);
		PrintTree(T2);

		if (Similar(T1, T2))
			break;

		Destroy(T1);	
		Destroy(T2);	
	}

	return 0;
#if 0
	BiTNode list;

	list.data = -1;
	list.lchild = list.rchild = NULL;
	ListLeaves(T, &list);
	PrintLeaves(&list);

	SearchAncestor(T, 10);
	for (i = 1; i <= 10; ++i)
		printf("PreOrder No.%d: %d\n", i, PreOrderK(T, i));
	Swap(T);
	ComputeDistAndDepth(T);
	PrintTree(T);
	printf("DsonNodes: %d\n", DsonNodes(T));
	Destroy(T);

	while (1) {
		T = Create(A, 10);
		ComputeDistAndDepth(T);
		PrintTree(T);
		if (IsComplete(T))
			break;
		Destroy(T);
	}

	TElemType A[] = {-1, 1, 3, 6, 9, 10, 5, 8, 2, 4, 7};
	TElemType B[] = {-1, 9, 6, 10, 3, 8, 5, 1, 4, 2, 7};
	BiTree T;

	T = PreInCreat(A, B, 1, 10, 1, 10);
	ComputeDistAndDepth(T);
	PrintTree(T);

	TElemType pre[7] = {1,2,3,4,5,6,7};
	TElemType post[7];
	int i;
	
	Pre2Post(pre, 0, 6, post, 0, 6);
	for (i = 0; i < 7; ++i)
		printf("%d ", post[i]);
	printf("\n");
#endif
}
