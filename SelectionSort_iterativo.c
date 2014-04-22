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
static void selection_sort(list_f *h);

int i = 0;

int main(void)
{
	list_f *h = NULL;
	srand(time(NULL));
	h = reclist(h);
	printlist(h);
	selection_sort(h);
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

static void selection_sort(list_f *h)
{
	list_f *temp = NULL, *min = NULL, *tmp = NULL;
	int i;
	for (tmp = h; tmp->next; tmp = tmp->next) {
		min = tmp;
		for (temp = tmp->next; temp; temp = temp->next) {
			if (temp->x < min->x)
				min = temp;
		}
		if (min != tmp) {
			i = tmp->x;
			tmp->x = min->x;
			min->x = i;
		}
	}
}
