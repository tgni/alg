#include <stdio.h>
#include <stdlib.h>
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


int32_t VisitNode(BiThrNode *p)
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

int main(void)
{
	BiThrTree T, Thrt;

	T = CreateBiThrTree();
	InOrderTraverse(T, VisitNode);

	InOrderThreading(&Thrt, T);
	InOrderTraverse_Thr(Thrt, VisitNode);

	return 0;
}
