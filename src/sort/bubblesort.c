#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void print_array(int a[], int n)
{
        int i;
        for (i=0; i<n; i++)        
                printf("%d ", a[i]);
        printf("\n");
}

void swap(int *a, int *b)
{
        int p;
        p = *a;
        *a = *b;
        *b = p;
}

void bubble_sort(int a[], int n)
{
        int i, j;
        for (i=0; i<n-1; i++)
                for (j=1; j<n-i; j++)
                        if (a[j-1] > a[j])
                                swap(&a[j-1], &a[j]);

}

int main(void)
{
        int A[] = {22, 14, 17, 5, 6, 10, 19, 13, 32, 21}; 
        print_array(A, 10);
        bubble_sort(A, 10);
        print_array(A, 10);
}
