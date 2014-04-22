#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000

typedef struct list_int {
	int x;
	struct list_int *next;
} list_f;

static list_f *reclist(list_f *h);
static void printlist(list_f *h);
static void freelist(list_f *h);
static void quicksort(list_f **h, list_f *end);

int i = 0;

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
	if (((*h) != pivot) && ((*h)->next != pivot))
		quicksort(h, pivot);
	if ((pivot->next) && (pivot->next->next))
		quicksort(&pivot->next, NULL);
	return;
}
