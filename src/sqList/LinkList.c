#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ElemType int

typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

/* delete - recursively delete one or more nodes from L with data as x.
 * @L: LinkList without head
 * @x:
 * Note: Using double pointer to delete L's nodes.
 * when doing *L = (*L)->next, *L can't be replaced by another pointer! 
 * the following code is WRONG:
 *	q = *L;
 *	q = q->next;
 */
void __Delete(LinkList *L, ElemType x)
{
	LinkList p;

	if (*L == NULL)
		return;

	if ((*L)->data == x) {
		p = *L;
		*L = (*L)->next;
		free(p);
		__Delete(L, x);
	} else {
		__Delete(&(*L)->next, x);
	}
}


LinkList Create(int nr)
{
	int i;
	LinkList p, L;
	
	L = (LinkList)malloc(sizeof(LNode));
	L->data = rand() % nr;
	p = L;

	for (i = 0; i < nr; ++i) {
		p->next = (LinkList)malloc(sizeof(LNode));
		p = p->next;
		p->data = rand() % nr;
	}

	p->next = NULL;

	return L;
}

void Delete(LinkList L, ElemType x)
{
	LNode *p = L->next, *pre = L, *q;

	while (p) {
		if (p->data == x) {
			q = p;
			p = p->next;
			pre->next = p;
			free(q);
		} else {
			pre = p;
			p   = p->next;
		}
	}
}

void DeleteXY(LinkList L, ElemType x, ElemType y)
{
	LNode *p = L->next, *pre = L, *q;

	while (p) {
		if (p->data > x && p->data < y) {
			q = p;
			p = p->next;
			pre->next = p;
			free(q);
		} else {
			pre = p;
			p   = p->next;
		}
	}
}

/* Suppose only one minimum in list */
void DeleteMin(LinkList L)
{
	LNode *pre = L, *p = pre->next;
	LNode *minpre = pre, *minp = p;

	while (p) {
		if (p->data < minp->data) {
			minp = p;	
			minpre = pre;
		}

		pre = p;
		p = p->next;
	}

	minpre->next = minp->next;
	free(minp);

	return;
}

/* Suppose L is sorted. */
void DeleteDup(LinkList L)
{
	LNode *pre, *p;

	if (!(pre = L->next))
		return;

	p = pre->next;

	while (p) {
		if (pre->data == p->data) {
			pre->next = p->next;
			free(p);
			p = pre->next;
		} else {
			pre = p;
			p = p->next;
		}
	}

	return;
}

void Reverse(LinkList L)
{
	LNode *p, *r;

	p = L->next;
	L->next = NULL;

	while (p) {
		r = p->next;
		p->next = L->next;
		L->next = p;
		p = r;
	}

	return;
}

void Sort(LinkList L)
{
	LNode *p, *r, *pre;

	p = L->next;
	r = p->next;
	p->next = NULL;
	p = r;

	while (p) {
		r = p->next;
		pre = L;

		/* find pos to insert p */
		while (pre->next && pre->next->data < p->data)
			pre = pre->next;
		/* insert p */
		p->next = pre->next;
		pre->next = p;

		p = r;
	}

	return;
}

LinkList Create2(int nr)
{
	int i;
	LinkList p, L;
	
	L = (LinkList)malloc(sizeof(LNode));
	L->data = -1;
	p = L;

	for (i = 0; i < nr; ++i) {
		p->next = (LinkList)malloc(sizeof(LNode));
		p = p->next;
		p->data = rand() % nr;
	}

	p->next = NULL;

	return L;
}

void PrintReverse(LinkList L)
{
	if (L->next) {
		PrintReverse(L->next);
	}
	printf("%d ", L->data);
}



void PrintList(LinkList L)
{
	while (L) {
		printf("%d ", L->data);
		L = L->next;
	}
	printf("\n");
}

LinkList Split(LinkList A)
{
	LinkList B;
	LNode *p, *r1 = A, *r2;
	int i = 0;

	B = (LinkList)malloc(sizeof(LNode));
	B->data = -1;
	r2 = B;

	p = A->next;
	while (p) {
		if (++i % 2 != 0) {
			r1->next = p;
			r1 = r1->next;
		} else {
			r2->next = p;
			r2 = r2->next;
		}
		p = p->next;
	}
	
	r1->next = NULL;
	r2->next = NULL;

	return B;
}

void Merge(LinkList A, LinkList B)
{

}


int main(void)
{
	LinkList L, A;

	srand(time(NULL));

	L = Create2(10);
	PrintList(L);
	//Delete(L, 0);
	//DeleteXY(L, 0, 5);
	//DeleteMin(L);
	//Sort(L);
	//PrintList(L);
	//DeleteDup(L);
	//Reverse(L);	
	//A = Split(L); 
	//PrintList(L);
	//PrintList(A);

	return 0;
}
