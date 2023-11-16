#include <stdio.h>

typedef struct {
	int i; //taskId
	int d; //deadTime
	int w; //penalty
} task_t;

task_t TASK[7] = {
	{2, 2, 60},
	{4, 3, 40},
	{1, 4, 70},
	{7, 6, 10},
	{3, 4, 50},
	{5, 1, 30},
	{6, 4, 20},
};

void sort_by_w(task_t *task[], int n)
{
	task_t *temp; 
	int i, j;

	for (i = 0; i < n; ++i) {
		for (j = i; j < n; ++j) {
			if (task[i]->w < task[j]->w) {
				temp    = task[i];
				task[i] = task[j];
				task[j] = temp;
			}
		}
	}

	return;
}

void sort_by_d(task_t *task[], int n)
{
	task_t *temp; 
	int i, j;

	for (i = 0; i < n; ++i) {
		for (j = i; j < n; ++j) {
			if (task[i]->d > task[j]->d) {
				temp    = task[i];
				task[i] = task[j];
				task[j] = temp;
			}
		}
	}

	return;
}

int matriod_sort(task_t *task[], int n)
{
#define MAX	7
	int i, early_idx = 0, late_idx = 0, max_t = 0;
	task_t *early[MAX], *late[MAX];

	if (n > MAX) {
		printf("err: max %d n %d\n", MAX, n);
		return -1;
	}
	
	for (i = 0; i < n; ++i) {
		if (max_t < task[i]->d)
			max_t = task[i]->d;

		if (task[i]->d <= max_t) {
			early[early_idx++] = task[i];
		}

		if (early_idx > max_t) {
			early_idx--;
			late[late_idx++] = task[i];
		}
	}

	for (i = 0; i < early_idx; ++i) {
		task[i] = early[i];
	}

	for (i = 0; i < late_idx; ++i) {
		task[i+early_idx] = late[i];
	}

	return early_idx;
}

void print_task(char *prefix, task_t *task[], int n)
{
	int i;

	printf("%s\n", prefix);
	for (i = 0; i < n; ++i) {
		printf(" A%d d %d w %d\n", task[i]->i, task[i]->d, task[i]->w);
	}
	printf("\n");
}

int main()
{
	task_t *out[7];
	int i, t;

	for (i = 0; i < 7; ++i)
		out[i] = &TASK[i];

	print_task("orig:", out, 7);
	sort_by_w(out, 7);	
	print_task("sort by w:", out, 7);
	t = matriod_sort(out, 7);
	print_task("matriod sort:", out, 7);
	sort_by_d(out, t);
	print_task("sort by d:", out, 7);


	return 0;
}
