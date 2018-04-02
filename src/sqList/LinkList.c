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
void delete(LinkList *L, ElemType x)
{
	LinkList p;

	if (*L == NULL)
		return;

	if ((*L)->data == x) {
		p = *L;
		*L = (*L)->next;
		free(p);
		delete(L, x);
	} else {
		delete(&(*L)->next, x);
	}
}


LinkList create(int nr)
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

/* LinkList with HEADER */
void delete2(LinkList *L, ElemType x)
{
	LNode *p = (*L)->next, *pre = *L, *q;

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

LinkList DeleteMin(LinkList *L)
{
	LNode *pre = *L, *p = pre->next;
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

	return *L;
}

LinkList Reverse(LinkList *L)
{
	LNode *p, *r;

	p = (*L)->next;
	(*L)->next = NULL;

	while (p) {
		r = p->next; //save p->next
		p->next = (*L)->next;
		(*L)->next = p;
		p = r;	     //restore p->next
	}

	return *L;
}

void Sort(LinkList *L)
{
	LNode *p, *r, *pre;

	p = (*L)->next;
	r = p->next;
	p->next = NULL;
	p = r;

	while (p) {
		r = p->next;
		//pre points to result L
		pre = *L;
		//find position to insert p
		while (pre->next && pre->next->data < p->data)
			pre = pre->next;
		//insert p
		p->next = pre->next;
		pre->next = p;
		//p = p->next
		p = r;
	}

	return;
}

LinkList create2(int nr)
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

void printReverse(LinkList L)
{
	if (L->next) {
		printReverse(L->next);
	}
	printf("%d ", L->data);
}



void printList(LinkList L)
{
	while (L) {
		printf("%d ", L->data);
		L = L->next;
	}
	printf("\n");
}


int main(void)
{
	LinkList L;

	srand(time(NULL));
	L = create2(10);
	printList(L);
	Sort(&L);
	printList(L);
	//printList(L);
	//printReverse(L);
	//Reverse(&L);
	/*
	delete2(&L, 0);
	delete2(&L, 1);
	delete2(&L, 2);
	delete2(&L, 3);
	printList(L);
	*/

	return 0;
}
