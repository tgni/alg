#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ElemType int
#define FALSE  0 
#define TRUE   1

typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LNode, *LinkList;

typedef struct DNode {
	ElemType data;
	struct DNode *prior, *next;
} DNode, *DLinkList;

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

/* Insertion Sort */
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

LinkList Create3(ElemType A[], int nr)
{
	int i;
	LinkList p, L;
	
	L = (LinkList)malloc(sizeof(LNode));
	L->data = -1;
	p = L;

	for (i = 0; i < nr; ++i) {
		p->next = (LinkList)malloc(sizeof(LNode));
		p = p->next;
		p->data = A[i];
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

/* Merge two sorted A & B */
LinkList Merge(LinkList A, LinkList B)
{
	LinkList R;
	LNode *p, *q, *r;

	R = (LinkList)malloc(sizeof(LNode));
	R->data = -1;
	R->next = NULL;

	p = A->next;
	q = B->next;

	while (p && q) {
		if (p->data < q->data) {
			r = p->next;
			p->next = R->next;
			R->next = p;
			p = r;
		} else {
			r = q->next;
			q->next = R->next; 
			R->next = q;
			q = r;
		}
	}

	p = (q) ? q : p;

	while (p) {
		r = p->next;
		p->next = R->next;
		R->next = p;
		p = r;
	}

	free(A);
	free(B);

	return R;
}

/* Extract common elements from A and B, which are sorted.  */
LinkList Comm(LinkList A, LinkList B)
{
	LinkList C;
	LNode *p, *q, *r;

	C = (LinkList)malloc(sizeof(LNode));
	C->data = -1;
	C->next = NULL;

	p = A->next;
	q = B->next;

	while (p && q) {
		if (p->data == q->data) {
			r = (LNode *)malloc(sizeof(LNode));
			r->data = p->data;
			r->next = C->next;
			C->next = r;
			p = p->next;
			q = q->next;
		} else if (p->data > q->data) {
			q = q->next;	
		} else {
			p = p->next;
		}
	}

	if (!C->next) {
		free(C);
		return NULL;
	}

	//Sort(C);
	//DeleteDup(C);

	return C;
}

/* A = A n B, A and B are increasing sorted.  */
void Union(LinkList A, LinkList B)
{
	LNode *p, *q, *r, *t;	

	p = A->next;
	q = B->next;
	r = A;

	A->next = NULL;
	while (p && q) {
		if (p->data == q->data)	{
			r->next = p;				
			r = r->next;
			p = p->next;
			t = q;
			q = q->next;
		} else if (p->data > q->data) {
			t = q;
			q = q->next;
		} else {
			t = p;
			p = p->next;
		}
		free(t);
	}
	r->next = NULL;
	DeleteDup(A);

	while (p) {
		t = p;
		p = p->next;
		free(p);
	}
	while (q) {
		t = q;
		q = q->next;
		free(q);
	}
	free(B);

	return;
}

int Pattern(LinkList A, LinkList B)
{
	LNode *p, *pre, *q;

	pre = p = A->next;
	q = B->next;

	while (p && q) {
		if (p->data == q->data) {
			p = p->next;
			q = q->next;
		} else {
			pre = pre->next;	
			p = pre;
			q = B->next;
		}
	}
	
	return q ? FALSE : TRUE;
}

DLinkList *CreateDLinkList(ElemType A[], int nr)
{

}


int main(void)
{
	//ElemType A[10] = {1, 6, 7, 4, 6, 8, 6, 7, 8, 10};
	ElemType A[10] = {1, 6, 7, 4, 6, 8, 6, 7, 0, 10};
	ElemType B[3] = {6, 7, 8};
	LinkList La, Lb;

	La = Create3(A, 10);
	Lb = Create3(B, 3);

	//L = Create2(10);
	//PrintList(L);
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
	
	PrintList(La);
	PrintList(Lb);
	printf("B is %s sub of A.\n", Pattern(La, Lb) ? "" : "not");
	//Union(A, B);	
	//PrintList(A);

	return 0;
}
