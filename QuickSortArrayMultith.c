#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 100000
#define MAX_THREAD 20

typedef struct {
	int init;
	int end;
} a;

static void newarray(void);
static void printarray(void);
static void quicksort(a *tmp);
static void selectionsort(a *tmp);

int thread_num = 0;
int array[N];

int main(void)
{
	a tmp;
	tmp.init = 0;
	tmp.end = N;
	srand(time(NULL));
	newarray();
	printarray();
	quicksort(&tmp);
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

static void quicksort(a *tmp)
{
	pthread_t second_half_thread;
	int created = 0;
	a temp;
	int pivot, i, j, x;
	pivot = tmp->init;
	for (i = tmp->init + 1; i < tmp->end; i++) {
		if (array[i] < array[pivot]) {
			for (j = i; j > tmp->init; j--) {
				x = array[j - 1];
				array[j - 1] = array[j];
				array[j] = x;
			}
			pivot++;
		}
	}
	temp.init = pivot + 1;
	temp.end = tmp->end;
	tmp->end = pivot;
	if (temp.end - temp.init < N / MAX_THREAD) {
		selectionsort(&temp);
	} else {
		if (thread_num < MAX_THREAD) {
			thread_num++;
			created = 1;
			pthread_create(&second_half_thread, NULL, (void *)quicksort, &temp);
		} else {
			quicksort(&temp);
		}
	}
	if (tmp->end - tmp->init < N / MAX_THREAD)
		selectionsort(tmp);
	else
		quicksort(tmp);
	if (created) {
		pthread_join(second_half_thread, NULL);
		thread_num--;
	}
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
