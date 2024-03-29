#include <stdio.h>
#include "heap.h"

int main(){
	heap* myheap = heap_init();

	int maxKey = 100; //100 to 100 thousand by power of 10
	for (int i = 1; i<maxKey; i+=5) {
		heap_insert(&myheap, i, NULL);
	}
	
	printf("original fib heap:\n");
	heap_display(&myheap);

	while (!is_empty(myheap)){
		data d = heap_extract_min(&myheap);
		printf("after extract %d\n", d.key);
		heap_display(&myheap);
	}
#if 0
	for (int i = 1; i<maxKey; i+=3) {
		nd = heap_insert(&myheap, i, NULL);
	}

	printf("delete %d\n", nd->key);
	heap_delete(&myheap, nd);
	heap_display(&myheap);
#endif

	return 0;
}
