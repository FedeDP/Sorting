#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10000
#define MAX_THREAD 10

typedef struct list_int {
	int x;
	struct list_int *next;
} list_f;

static list_f *reclist(list_f *h);
static void printlist(list_f *h);
static void freelist(list_f *h);
static void quicksort(list_f **h, list_f *end);
static void second_half(list_f **h);

int i = 0;
int thread_num = 0;

int main(void)
{
	list_f *h = NULL;
	srand(time(NULL));
	h = reclist(h);
	printlist(h);
	quicksort(&h, NULL);
	printlist(h);
	freelist(h);
	return 0;
}

static list_f *reclist(list_f *h)
{
	h = malloc(sizeof(list_f));
	if ((h) && (i != N)) {
		h->x = rand()%N + 1;
		i++;
		h->next = reclist(h->next);
	} else {
		h = NULL;
	}
	return h;
}

static void printlist(list_f *h)
{
	if (h) {
		printf("\n%d", h->x);
		return printlist(h->next);
	}
}

static void freelist(list_f *h)
{
	if (h) {
		freelist(h->next);
		free(h);
	}
}

static void quicksort(list_f **h, list_f *end)
{
	list_f *temp = NULL, *pivot = NULL, *tmp = NULL;
	pthread_t second_half_thread;
	int created = 0;
	pivot = *h;
	for (temp = *h; temp->next != end; temp = temp->next) {
		while ((temp->next != end) && (temp->next->x < pivot->x)) {
			tmp = temp->next;
			temp->next = temp->next->next;
			tmp->next = *h;
			*h = tmp;
		}
		if (temp->next == end)
			break;
	}
	if ((pivot->next) && (pivot->next->next)) {
		if (thread_num < MAX_THREAD) {
			thread_num++;
			created = 1;
			pthread_create(&second_half_thread, NULL, (void *)second_half, &pivot->next);
		} else {
			quicksort(&pivot->next, NULL);
		}
	}
	if (((*h) != pivot) && ((*h)->next != pivot))
		quicksort(h, pivot);
	if (created) {
		pthread_join(second_half_thread, NULL);
		thread_num--;
	}
	return;
}

static void second_half(list_f **h)
{
	list_f *temp = NULL, *pivot = NULL, *tmp = NULL;
	pthread_t second_half_thread;
	int created = 0;
	pivot = *h;
	for (temp = *h; temp->next; temp = temp->next) {
		while ((temp->next) && (temp->next->x < pivot->x)) {
			tmp = temp->next;
			temp->next = temp->next->next;
			tmp->next = *h;
			*h = tmp;
		}
		if (!temp->next)
			break;
	}
	if ((pivot->next) && (pivot->next->next)) {
		if (thread_num < MAX_THREAD) {
			thread_num++;
			created = 1;
			pthread_create(&second_half_thread, NULL, (void *)second_half, &pivot->next);
		} else {
			quicksort(&pivot->next, NULL);
		}
	}
	if (((*h) != pivot) && ((*h)->next != pivot))
		quicksort(h, pivot);
	if (created) {
		pthread_join(second_half_thread, NULL);
		thread_num--;
	}
	return;
}
