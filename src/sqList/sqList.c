#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define false	(0)
#define true	(1)

typedef int ElemType;
typedef unsigned char bool;

#define MaxSize	50
typedef struct {
	ElemType data[MaxSize];
	int length;
} SqList;

void InsertSort(SqList *sq)
{
	int i, j, tmp;

	for (i = 1; i < sq->length; ++i) {
		tmp = sq->data[i];
		for (j = i; j > 0 && sq->data[j - 1] > tmp; j--)
			sq->data[j] = sq->data[j - 1];
		sq->data[j] = tmp;
	}
}


bool DeleteMin(SqList *sq, ElemType *value)
{
	int pos = 0, i; //Never forget set pos zero!

	if (sq->length == 0)
		return false;
	
	*value = sq->data[0];
	for (i = 1; i < sq->length; ++i) {
		if (*value > sq->data[i]) {
			*value = sq->data[i];
			pos    = i;
		}
	}
	sq->data[pos] = sq->data[sq->length - 1];
	--sq->length;

	return true;
}

void Reverse(SqList *sq)
{
	int i;
	ElemType tmp;

	for (i = 0; i < sq->length/2; ++i) {
		tmp = sq->data[i];
		sq->data[i] = sq->data[sq->length-1-i];
		sq->data[sq->length-1-i] = tmp;
	}
}

void DeleteX(SqList *sq, ElemType x)
{
	int i, k = 0;
	
	for (i = 0; i < sq->length; ++i) {
		if (sq->data[i] != x) {
			sq->data[k] = sq->data[i];
			k++;
		}
	}

	sq->length = k;
}


//SqList is on rising order
bool DeleteST(SqList *sq, ElemType s, ElemType t)
{
	int i, j, len;
	
	if (s >= t || sq->length == 0)
		return false;

	for (i = 0; i < sq->length && sq->data[i] < s; ++i)
		;
	if (i >= sq->length)
		return false;

	for (j = i; j < sq->length && sq->data[j] <= t; ++j)
		;
	
	for (++j; j < sq->length; ++i, ++j)
		sq->data[i] = sq->data[j];
	sq->length = i; //beautiful!

	return true;
}

bool _DeleteST(SqList *sq, ElemType s, ElemType t)
{
	int i, k = 0;

	if (s >= t || sq->length == 0)
		return false;

	for (i = 0; i < sq->length; ++i) {
		if (sq->data[i] < s || sq->data[i] > t) {
			sq->data[k] = sq->data[i];
			++k;
		}
	}
	sq->length = k;

	return true;
}

//sorted sqlist
bool DeleteDup(SqList *sq)
{
	int i, j;

	if (sq->length == 0)
		return false;

	for (i = 0, j = 1; j < sq->length; ++j) {
		if (sq->data[i] != sq->data[j])
			sq->data[++i] = sq->data[j];
	}
	sq->length = i+1;

	return true;
}

//reverse array from s to e
bool ReverseArray(ElemType A[], int size, int s, int e)
{
	int i, mid;
	ElemType tmp;

	if (s >= e || e >= size)
		return false;
/*	
	for (i = s; i <= s + (e-s+1)/2; ++i) {
		tmp      = A[i];
		A[i]     = A[e-i+s];
		A[e-i+s] = tmp;
	}
*/
	mid = (s+e)/2;
	for (i = 0; i < mid-s; ++i) {
		tmp    = A[s+i];
		A[s+i] = A[e-i];
		A[e-i] = tmp;
	}

	return true;
}


bool Merge(SqList *s, SqList *t, SqList *r)
{
	int i = 0, j = 0, k = 0;

	if (s->length + t->length > r->length)
		return false;

	while (i < s->length && j < t->length) {
		if (s->data[i] < t->data[j]) {
			r->data[k++] = s->data[i++];	
		} else {
			r->data[k++] = t->data[j++];
		}
	}

	while (i < s->length)
		r->data[k++] = s->data[i++];
	while (j < t->length)
		r->data[k++] = t->data[j++];
	r->length = k;

	return true;
}

void PrintSqList(SqList *sq)
{
	int i;

	printf("SqList: ");
	for (i = 0; i < sq->length; ++i) 
		printf(" %d", sq->data[i]);
	printf("\n");
}

int main(void)
{
	SqList L;
	int i, m, n;
	ElemType min;

	srand(time(NULL));

	for (i = 0; i < MaxSize; ++i) {
		L.data[i] = rand() % MaxSize;
	}
	L.length = MaxSize;

	//DeleteMin(&L, &min);
	//printf("Minimum is %d\n", min);
	
	//printf("Delete 33 if exists!\n");
	//DeleteX(&L, 33);
	
	//Reverse(&L);
	
	//InsertSort(&L);
	//PrintSqList(&L);
	//printf("Delete between 20 - 35\n");
	//DeleteST(&L, 20, 35);
	//_DeleteST(&L, 20, 35);
	
	//InsertSort(&L);
	//PrintSqList(&L);
	//DeleteDup(&L);
	

	InsertSort(&L);
	PrintSqList(&L);
	m = 20; n = L.length - m;
	printf("Reverse m = %d, n = %d\n", m, n);
	ReverseArray(L.data, L.length, 0, L.length-1);
	ReverseArray(L.data, L.length, 0, n - 1);
	ReverseArray(L.data, L.length, n, L.length-1);
	PrintSqList(&L);

	return 0;
}
