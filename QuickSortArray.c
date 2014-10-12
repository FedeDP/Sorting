#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000

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
	int i, x;
	int pivot_index = init;
	int pivot_value = array[pivot_index];
	if (end - init > 1) {
		for (i = init + 1; i < end; i++) {
			if (array[i] < pivot_value) {
				array[pivot_index] = array[pivot_index + 1];
				array[pivot_index + 1] = pivot_value;
				if (i != pivot_index + 1) {
					x = array[pivot_index];
					array[pivot_index] = array[i];
					array[i] = x;
				}
				pivot_index++;
			}
		}
		quicksort(init, pivot_index);
		quicksort(pivot_index + 1, end);
	}
}
