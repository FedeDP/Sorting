#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

typedef struct list_int {
	int x;
	struct list_int *next;
} list_f;

static list_f *reclist(list_f *h);
static void printlist(list_f *h);
static void freelist(list_f *h);
static void sortlist(list_f *h);
static int bubblesort(list_f *h, int swap);

int i = 0;

int main(void)
{
	list_f *h = NULL;
	srand(time(NULL));
	h = reclist(h);
	printlist(h);
	sortlist(h);
	printlist(h);
	freelist(h);
	return 0;
}

static list_f *reclist(list_f *h)
{
	h = malloc(sizeof(list_f));
	if ((h) && (i != N)) {
		h->x = rand()%N+1;
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

static void sortlist(list_f *h)
{
	list_f *temp = NULL, *tmp = NULL;
	int swap = 1;
	for (tmp = h->next; (tmp) && (swap); tmp = tmp->next) {
		swap = 0;
		for (temp = h; temp->next; temp = temp->next) {
			if (temp->x > temp->next->x) {
				swap = 1;
				i = temp->next->x;
				temp->next->x = temp->x;
				temp->x = i;
			}
		}
	}
}
