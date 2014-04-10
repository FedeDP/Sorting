#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define N 1000
#define MAX_THREAD 10

typedef struct list_int{
  int x;
  struct list_int *next;
}list_f;

list_f *reclist (list_f *h);
void printlist (list_f *h);
void freelist (list_f *h);
void quicksort (list_f **h, list_f *end);
void second_half(list_f **h);

int i = 0;
int thread_num = 0;

int main()
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

void quicksort(list_f **h, list_f *end){ 
  list_f *temp = NULL, *pivot = NULL, *tmp = NULL;
  pthread_t second_half_thread;
  int created=0;
  pivot = *h;
  for(temp = *h; temp->next != end; temp = temp->next){
    while((temp->next != end) && (temp->next->x < pivot->x)){
      tmp = temp->next;
      temp->next = temp->next->next;
      tmp->next = *h;
      *h = tmp;
    }
    if(temp->next == end)
      break;
  }
  if((pivot->next) && (pivot->next->next)){
    thread_num++;
    created=1;
    pthread_create(&second_half_thread, NULL, (void*)second_half, &pivot->next);
  }
  if(((*h) != pivot) && ((*h)->next != pivot))
    quicksort(h, pivot);
  if(created){ 
    pthread_join(second_half_thread, NULL);
    thread_num--;
  }
  return;
}

void second_half(list_f **h){
  list_f *temp = NULL, *pivot = NULL, *tmp = NULL;
  pthread_t second_half_thread;
  int created=0;
  pivot = *h;
  for(temp = *h; temp->next; temp = temp->next){
    while((temp->next) && (temp->next->x < pivot->x)){
      tmp = temp->next;
      temp->next = temp->next->next;
      tmp->next = *h;
      *h = tmp;
    }
    if(!temp->next)
      break;
  }
  if((pivot->next) && (pivot->next->next)){
    if(thread_num < MAX_THREAD){
      thread_num++;
      created=1;
      pthread_create(&second_half_thread, NULL, (void*)second_half, &pivot->next);
    }else
      quicksort(&pivot->next, NULL);
  }
  if(((*h) != pivot) && ((*h)->next != pivot))
    quicksort(h, pivot);
  if(created){ 
    pthread_join(second_half_thread, NULL);
    thread_num--;
  }
  return;
}
