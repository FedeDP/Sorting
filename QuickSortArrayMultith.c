#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 100000
#define LOWEST_DISTANCE 1000

typedef struct {
	int init;
	int end;
} a;

static void newarray(void);
static void printarray(void);
static void quicksort(a *tmp);
static void selectionsort(a *tmp);

int array[N];

int main(void)
{
	a tmp;
	tmp.init = 0;
	tmp.end = N;
	srand(time(NULL));
	newarray();
	//printarray();
	quicksort(&tmp);
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

static void quicksort(a *tmp)
{
	pthread_t second_half_thread;
	int created = 0;
	a temp;
	int i, x;
	int pivot_index = tmp->init;
	int pivot_value = array[pivot_index];
	for (i = tmp->init + 1; i < tmp->end; i++) {
		if (array[i] < pivot_value) {
			if (i != pivot_index + 1) {
				array[pivot_index] = array[pivot_index + 1];
				array[pivot_index + 1] = pivot_value;
			}
			x = array[pivot_index];
			array[pivot_index] = array[i];
			array[i] = x;
			pivot_index++;
		}
	}
	temp.init = pivot_index + 1;
	temp.end = tmp->end;
	tmp->end = pivot_index;
	if (temp.end - temp.init < LOWEST_DISTANCE) {
		selectionsort(&temp);
	} else {
		quicksort(&temp);
		created = 1;
		pthread_create(&second_half_thread, NULL, (void *)quicksort, &temp);
	}
	if (tmp->end - tmp->init < LOWEST_DISTANCE)
		selectionsort(tmp);
	else
		quicksort(tmp);
	if (created)
		pthread_join(second_half_thread, NULL);
}

static void selectionsort(a *tmp)
{
	int i, j, min, temp;
	for (i = tmp->init; i < tmp->end - 1; i++) {
		min = i;
		for (j = i + 1; j < tmp->end; j++) {
			if (array[j] < array[min])
				min = j;
		}
		if (min != i) {
			temp = array[min];
			array[min] = array[i];
			array[i] = temp;
		}
	}
}
