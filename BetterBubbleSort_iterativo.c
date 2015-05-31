#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 50000

static void generate_array(void);
static void printlist(void);
static void sortlist(void);

int array[N];

int main(void)
{
	srand(time(NULL));
    generate_array();
	printlist();
	sortlist();
	printlist();
	return 0;
}

static void generate_array(void)
{
    int i;
    for (i = 0; i < N; i++)
        array[i] = rand()%N + 1;
}

static void printlist(void)
{
    int i;
	for (i = 0; i < N; i++)
        printf("%d\n", array[i]);
}

static void sortlist(void)
{
	int swap = 1, i, j, temp;
	for (i = 1; (i < N) && (swap); i++) {
		swap = 0;
		for (j = i - 1; j < N - 1; j++) {
			if (array[j] > array[j + 1]) {
				swap = 1;
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}
		}
	}
}
