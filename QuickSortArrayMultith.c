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

void newarray();
void printarray();
void quicksort(a *tmp);

int thread_num = 0;
int array[N];

int main(void)
{
	srand(time(NULL));
	newarray(array);
	printarray(array);
	a tmp;
	tmp.init = 0;
	tmp.end = N;
	quicksort(&tmp);
	printarray(array);
	return 0;
}

void newarray()
{
	int i = 0;
	for (; i < N; i++)
		array[i] = rand()%N + 1;
}

void printarray()
{
	int i = 0;
	for (; i < N; i++)
		printf("%d\n", array[i]);
}

void quicksort(a *tmp)
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
	if (pivot + 1 < temp.end) {
		if (thread_num < MAX_THREAD) {
			thread_num++;
			created = 1;
			pthread_create(&second_half_thread, NULL, (void *)quicksort, &temp);
		} else {
			quicksort(&temp);
		}
	}
	if (pivot > tmp->init + 1)
		quicksort(tmp);
	if (created) {
		pthread_join(second_half_thread, NULL);
		thread_num--;
	}
	return;
}
