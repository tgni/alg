#ifndef __TOOL_H__

#define NELEMS(array)	(sizeof(array) / sizeof(array[0]))

extern void swap(int v[], int i, int j);
extern void qqsort(int v[], int left, int right);
extern void print_array(char *prompt, int v[], int n);
extern void shuffle(int v[], int n);

#endif /* __TOOL_H__ */
