#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000


static void newarray(void);
static void printarray(void);
static void selectionsort(void);

int array[N];

int main(void)
{
	srand(time(NULL));
	newarray();
	printarray();
	selectionsort();
	printarray();
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

static void selectionsort(void)
{
	int i, j, min, max, temp;
	for (i = 0; i < N / 2 - 1; i++) {
		min = i;
		max = i;
		for (j = i + 1; j < N - 1 - i; j++) {
			if (array[j] < array[min])
				min = j;
			else if (array[j] > array[max])
				max = j;
		}
		if (min != i) {
			temp = array[min];
			array[min] = array[i];
			array[i] = temp;
		}
		if (max != N - 1 - i) {
			temp = array[max];
			array[max] = array[N - 1 - i];
			array[N - 1 - i] = temp;
		}
	}
}
