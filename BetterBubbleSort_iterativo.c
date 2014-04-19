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
