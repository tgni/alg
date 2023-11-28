#include "use.h"
#ifdef  USE_FIBO_HEAP

#include <stdio.h>
#include <limits.h>
#include "heap.h"
#include "node.h"

heap* heap_init()
{
	return NULL;
}

elem* heap_add(heap** H, node* newNode);

elem* heap_insert(heap** H, int key, void* value)
{
	node* newNode = node_init(key, value);

	return heap_add(H, newNode);
}

int is_empty(heap* H)
{
	return H == NULL;
}

elem* heap_add(heap** H, node* newNode)
{
	node* oldNode = *H;

	newNode->parent = NULL;
	newNode->hasLostKid = 0;

	if (oldNode) { //nonempty heap
		node_add(oldNode, newNode);
		if (oldNode->key > newNode->key){ //new smallest
			*H = newNode;
		}
	} else { //previously empty heap
		newNode->left = newNode;
		newNode->right = newNode;
		*H = newNode;
	}

	return newNode;
}

data heap_min(heap* H)
{
	data d;
	node* head = H;

	d.key = head->key;
	d.value = head->value;

	return d;
}

void  heap_consolidate(heap** H);
void  heap_match_degrees(heap** H, node** A, node* x);
node* heap_link(heap** H, node* x, node* y);
void  heap_remove_from(heap** H, node* x);

data  heap_extract_min(heap** H)
{
	node* z = *H;
	data d = elem_data(z);
	node* first = z->kid;

	heap_remove_from(H, z);
	node_free(z);

	if (first) {
		//keep kids list, union with root list.
		node* current = first->right;
		while (current != first) {
			current->parent = NULL;
			current = current->right;
		}
		first->parent = NULL;
		*H = heap_union(*H, first);
	}
	heap_consolidate(H);
	return d;
}

void  heap_remove_from(heap** H, node* x)
{
	if (x->right == x) {
		*H = NULL;
	} else {
		x->left->right = x->right;
		x->right->left = x->left;
		*H = x->right;
	}
	x->left = x;
	x->right = x;
	x->parent = NULL;
}
void  heap_consolidate(heap** H)
{
	node* x = *H;
	node ** A; 

	if (!x) return;

	A = calloc(100, sizeof(node));

	memset(A, '\0', 100);

	node* last = x->left;
	while (x != last) {
		node* next = x->right;
		heap_match_degrees(H, A, x);
		x = next;
	}
	heap_match_degrees(H, A, last);

	*H = heap_init();
	for (int i=0; i<100; i++) {
		if (A[i]) {
			heap_add(H, A[i]);
		}
	}
	free(A);
}

void heap_match_degrees(heap** H, node** A, node* x)
{
	int d = x->degree;

	while (A[d]) {
		if (d > 99){
			exit(1);
		}
		node* y = A[d];
		if (y != x) {
			x = heap_link(H, x, y);
			A[d] = NULL;
			d++;
		} else {
			break;
		}
	}
	A[d] = x;
}

node* heap_link(heap** H, node* x, node* y){
	if (x->key > y->key){
		return heap_link(H, y, x);
	}

	heap_remove_from(H, y);

	if (x->kid) {
		node* z = x->kid;
		y->right = z;
		y->left = z->left;
		z->left->right = y;
		z->left = y;
	}
	y->parent = x;
	x->kid = y;
	x->degree++;
	y->hasLostKid = 0;

	return x;
}

heap* heap_union(heap* H1, heap* H2){
	if(!H1) return H2;
	if(!H2) return H1;

	if (heap_min(H2).key < heap_min(H1).key){
		return heap_union(H2, H1);
	}

	node* H1first = H1;
	node* H1last = H1first->left;
	node* H2first = H2;
	node* H2last = H2first->left;

	H1last->right = H2first;
	H2first->left = H1last;
	H2last->right = H1first;
	H1first->left = H2last;

	return H1first;
}

void cut(heap ** H, node *x, node *y)
{
	if (x->left == x) {
		assert(x->parent->degree == 1);
		y->kid = NULL;
	} else {
		assert(x->parent->degree > 1);
		x->left->right = x->right;
		x->right->left = x->left;
		y->kid = x->left;
	}
	y->degree--;

	heap_add(H, x);
}

void cascading_cut(heap ** H, node *y)
{
	node *z = y->parent;
	if (z) {
		if (!y->hasLostKid) {
			y->hasLostKid = 1;
		} else {
			cut(H, y, z);
			cascading_cut(H, z);
		}
	}
}

void heap_decrease_key(heap** H, elem* x, int newKey)
{
	node *y;

	assert(H && *H);
	assert(x && x->key >= newKey);

	x->key = newKey;
	y = x->parent;

	if(y && x->key < y->key) {
		cut(H, x, y);
		cascading_cut(H, y);
	}

	if (newKey < (*H)->key) {
		assert(!x->parent);
		*H = x;
	}
}

void  heap_delete(heap** H, elem* x)
{
	heap_decrease_key(H, x, INT_MIN);
	heap_extract_min(H);
}

data  elem_data(elem* x) 
{
	assert(x);
	data d;
	d.key = x->key;
	d.value = x->value;
	return d;
}

void heap_free(heap** H) 
{
	node* header = *H;
	node* first = header;

	if (header) {
		do {
			node_kill(header);
			header = header->right;
		} while (header != first);
	}

	*H = NULL;
}

void compute_level(heap ** H)
{
	node* first = *H;
	node* next = first;

	if (!first)
		return;
	do {
		if (next->parent) {
			next->level = next->parent->level + 1;
		} else {
			next->level = 0;
		}
		if (next->kid)
			compute_level(&next->kid);
		next= next->right;
	} while (next != first);

	return;
}

static int __last[99];
void display_node(node *n)
{
	int i;

	for (i = 1; i < n->level+1; ++i) {
		if (i == n->level) {
			printf("%s%s", __last[i] ? "\\" : "|", "--");
		} else {
			printf("%s", __last[i] ? "    " : "|   ");
		}
	}
	printf("%d\n", n->key);

	return;
}

void __heap_display(heap ** H)
{
	node* first = *H;
	node* next = first;

	if (!first)
		return;
	do {
		__last[next->level] = (next->right == first) ? 1 : 0;
		display_node(next);
		if (next->kid)
			__heap_display(&next->kid);
		next = next->right;
	} while (next != first);

	return;
}

void heap_display(heap ** H)
{
	compute_level(H);
	memset(__last, 0, sizeof(__last));
	__heap_display(H);
}

#else
int dummy = 1;
#endif
