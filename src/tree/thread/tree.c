#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"
#include "stack.h"

BiThrTree CreateBiThrTree(void)
{
	BiThrTree T;
	Stack S;
	char ch, cr;
	
	scanf("%c%c", &ch, &cr);
	if (ch == ' ')
		return NULL;

	if (!(T = (BiThrNode *)malloc(sizeof(BiThrNode))))
		return NULL;

	T->data = ch;
	printf("%c's lchild:\n", ch);
	T->lchild = CreateBiThrTree();
	printf("%c's rchild:\n", ch);
	T->rchild = CreateBiThrTree();

	return T;
}

int32_t InOrderTraverse(BiThrTree T, VisitFn Visit)
{
	Stack S;
	BiThrTree p;

	S = CreateStack();
	p = T;

	while (p || !IsEmpty(S)) {
		if (p) {
			Push(p, S);
			p = p->lchild;
		} else {
			p = (BiThrTree)Pop(S);
			Visit(p);
			p = p->rchild;
		}
	}

	return 0;
}


int32_t VisitBiThrNode(BiThrNode *p)
{
	printf("LTag: %d data: %c RTag: %d\n", p->LTag, p->data, p->RTag);
	return 0;
}

int32_t InOrderTraverse_Thr(BiThrTree T, VisitFn Visit)
{
	BiThrNode *p;

	p = T->lchild;
	while (p != T) {
		while (p->LTag == Link) p = p->lchild;	
		Visit(p);
		while (p->RTag == Thread && p->rchild != T) {
			p = p->rchild;
			Visit(p);
		}
		p = p->rchild;
	}

	return 0;
}


static BiThrNode *PRE = NULL;

void InThreading(BiThrTree p)
{
	if (!p)
		return;

	InThreading(p->lchild);

	if (!p->lchild) {
		p->LTag = Thread;
		p->lchild = PRE;
	}

	if (!PRE->rchild) {
		PRE->RTag = Thread;
		PRE->rchild = p;
	}

	PRE = p;
	InThreading(p->rchild);

	return;
}


int32_t InOrderThreading(BiThrTree *_Thrt, BiThrTree T)
{
	BiThrTree Thrt;

	if (!(*_Thrt = (BiThrTree)malloc(sizeof(BiThrNode))))
		return -1;
	Thrt = *_Thrt;

	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	
	if (!T) {
		Thrt->lchild = Thrt;
		return 0;
	}

	Thrt->lchild = T;
	PRE = Thrt;
	InThreading(T);
	PRE->rchild = Thrt;
	PRE->RTag = Thread;
	Thrt->rchild = PRE;

	return 0;
}

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
	p->depth = 0;

	if (!T) {
		T = p;
	} else {
		if (dir)
			pre->lchild = p;
		else
			pre->rchild = p;
		p->depth = pre->depth + 1;
	}

	return T;
}

BiTree CreateRandBiTree(TElemType A[], int nr)
{
	BiTree T = NULL;
	int i;

	for (i = 0; i < nr; ++i)
		T = Insert(T, A[i]);

	return T;
}

int32_t InOrder(BiTree T, VisitFn Visit)
{
	Stack S;
	BiTree p;
	int depth;

	S = CreateStack();
	p = T;

	while (p || !IsEmpty(S)) {
		if (p) {
			Push(p, S);
			p = p->lchild;
		} else {
			p = (BiTree)Pop(S);
			Visit(p);
			p = p->rchild;
		}
	}

	return 0;
}

int32_t VisitBiTNode(void *node)
{
	BiTNode *p = (BiTNode *)node;
	printf("%d\n", p->data);
	return 0;
}


#define NR_DEPTH_MAX	256
static int __LAST[NR_DEPTH_MAX]; 

void list_dir(BiTree T)
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
		list_dir(T->lchild);
	} else if (!T->lchild && T->rchild) {
		__LAST[T->depth] = 1;
		list_dir(T->rchild);
	} else {
		__LAST[T->depth] = 0;
		list_dir(T->lchild);
		__LAST[T->depth] = 1;
		list_dir(T->rchild);
	}
}

int main(void)
{
	BiTree T;
	TElemType A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	srand(time(NULL));
	
	T = CreateRandBiTree(A, 10);
	InOrder(T, VisitBiTNode);
	list_dir(T);

	return 0;
}
