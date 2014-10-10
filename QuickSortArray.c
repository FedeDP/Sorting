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
	int pivot, left, right, x;
	if (end - init > 1) {
		pivot = array[init];
		left = init;
		right = end;
		while (left <= right) {
			while (array[left] < pivot)
				left++;
			while (array[right] > pivot)
				right--;
			if (left <= right) {
				x = array[left];
				array[left] = array[right];
				array[right] = x;
				left++;
				right--;
			}
		}
        	quicksort(init, right);
		quicksort(left, end);
	}
}
