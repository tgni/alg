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

void PrintTree(BiTree T)
{
	Queue que;

	if (T == NULL)
		return;

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


int main(void)
{
	BiTree T;
	TElemType A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	srand(time(NULL));
	
	T = Create(A, 10);
	ComputeDistAndDepth(T);
	//PrintDir(T);
	PrintTree(T);
	InOrder(T);
	PreOrder(T);
	PostOrder(T);
	printf("Height: %d\n", GetHeight(T));


	return 0;
}
