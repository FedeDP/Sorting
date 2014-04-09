/*
 * TODO:  multithreaded quicksort function
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 1000  

typedef struct list_int{
  int x;
  struct list_int *next;
}list_f;

list_f *reclist (list_f *h);
void printlist (list_f *h);
void freelist (list_f *h);
list_f *quicksort (list_f *h, list_f *end);

int i=0;

int main()
{
list_f *h = NULL;
srand(time(NULL));
h = reclist(h);
printlist(h);
h = quicksort(h, NULL);
printlist(h);
freelist(h);
return 0;
}

list_f *reclist(list_f *h){
  if((h = malloc(sizeof(list_f))) && (i != N)){
    h->x = rand()%N + 1;
    i++;
    h->next = reclist(h->next);   
  }else
    h = NULL;
  return h;       
}

void printlist(list_f *h){
  if(h){
    printf("\n%d", h->x);
    return printlist(h->next);    
  }
}

void freelist(list_f *h){
  if(h){
    freelist(h->next);
    free(h);
  }
}

list_f *quicksort(list_f *h, list_f *end){  //VERY SLOW...
  list_f *temp = NULL, *pivot = NULL, *tmp = NULL;
  pivot = h;
  for(temp = h; temp->next != end; temp = temp->next){
    while((temp->next != end) && (temp->next->x <= pivot->x)){
      tmp = temp->next;
      temp->next = temp->next->next;
      tmp->next = h;
      h = tmp;
    }
    if(temp->next == end)
      break;
  }
  if((h != pivot) && (h->next != pivot))
    h = quicksort(h, pivot);
  if((pivot->next) && (pivot->next->next))
    pivot->next = quicksort(pivot->next, NULL);
return h;
}
