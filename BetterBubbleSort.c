#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000

typedef struct list_int {
	int x;
	struct list_int *next;
} list_f;

list_f *reclist(list_f *h);
void printlist(list_f *h);
void freelist(list_f *h);
void sortlist(list_f *h);
int bubblesort(list_f *h, int swap);

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

list_f *reclist(list_f *h)
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

void printlist(list_f *h)
{
	if (h) {
		printf("\n%d", h->x);
		return printlist(h->next);
	}
}

void freelist(list_f *h)
{
	if (h) {
		freelist(h->next);
		free(h);
	}
}

void sortlist(list_f *h)
{
	list_f *temp = NULL;
	for (temp = h->next; temp; temp = temp->next) {
		if (bubblesort(h, 0) == 0)
			break;
	}
}

int bubblesort(list_f *h, int swap)
{
	int tmp;
	if (h->next) {
		if (h->x > h->next->x) {
			swap = 1;
			tmp = h->next->x;
			h->next->x = h->x;
			h->x = tmp;
		}
	return bubblesort(h->next, swap);
	}
	return swap;
}
