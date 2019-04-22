#ifndef __TOOL_H__

#define NELEMS(array)	(sizeof(array) / sizeof(array[0]))

void print_array(int v[], int n);
void swap(int v[], int i, int j);
void qqsort(int v[], int left, int right);
void print_array(int v[], int n);
void shuffle(int v[], int n);

#endif /* __TOOL_H__ */
