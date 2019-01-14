#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tree.h"
#include "stack.h"

typedef enum PointerTag {
	Link,
	Thread
} PointerTag;


typedef struct BiThrNode {
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
} BiThrNode, * BiThrTree;

BiThrTree Insert(BiThrTree T, TElemType x)
{
	BiThrNode *pre, *p;
	int dir = 0;

	/* find random leaf */
	pre = p = T;
	while (p) {
		dir = rand() % 2;
		pre = p;
		p = (dir) ? p->lchild : p->rchild;
	}

	if (!(p = (BiThrNode *)malloc(sizeof(BiThrNode))))
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

BiThrTree Create(TElemType A[], int nr)
{
	BiThrTree T = NULL;
	int i;

	for (i = 0; i < nr; ++i)
		T = Insert(T, A[i]);

	return T;
}

int32_t InOrder(BiThrTree T, VisitFn Visit)
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


int32_t Visit(BiThrNode *p)
{
	printf("LTag: %d data: %c RTag: %d\n", p->LTag, p->data, p->RTag);
	return 0;
}

int32_t InOrderThr(BiThrTree T, VisitFn Visit)
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
