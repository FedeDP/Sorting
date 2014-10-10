#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

static void newarray(void);
static void printarray(void);
static void quicksort(int init, int end);

int array[N];

int main(void)
{
	srand(time(NULL));
	newarray();
	//printarray();
	quicksort(0, N);
	//printarray();
	return 0;
}

static void newarray(void)
{
	int i = 0;
	for (; i < N; i++)
		array[i] = rand()%N + 1;
}

static void printarray(void)
{
	int i = 0;
	for (; i < N; i++)
		printf("%d\n", array[i]);
}

static void quicksort(int init, int end)
{
	int i, j, x;
	int pivot_index = init;
	int pivot_value = array[pivot_index];
	for (i = init + 1; i < end; i++) {
		if (array[i] < pivot_value) {
			for (j = i; j > pivot_index; j--) {
				x = array[j - 1];
				array[j - 1] = array[j];
				array[j] = x;
			}
			pivot_index++;
		}
	}
	if ((init != pivot_index) && (init + 1 != pivot_index))
		quicksort(init, pivot_index);
	if (pivot_index + 2 < end)
		quicksort(pivot_index + 1, end);
}
