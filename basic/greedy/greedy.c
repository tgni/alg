#include <stdio.h>

#define DenoNum         (4)
static int C[DenoNum] = {25, 10, 5, 1};
static int D[DenoNum] = {0};

int greedy(int N)
{
        int i;

        for (i = 0; i < DenoNum; i++) {
                D[i] = 0; 
                while ( N >= C[i]) {
                        D[i]++;
                        N -= C[i];
                }
        }

        return 0;
}

int printDeno(void)
{
        int i;

        printf("D: ");
        for (i = 0; i < DenoNum; i++)
                printf("%d ", D[i]);
        printf("\n");

        return 0;
}

int main(void)
{
        greedy(67);
        printDeno();        

        return 0;
}
