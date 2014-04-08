#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000

typedef struct list_int{
	int x;
	struct list_int *next;
}list_f;

list_f *reclist(list_f *h);
void printlist(list_f *h);
void freelist(list_f *h);
void selection_sort(list_f *h);

int i=0;

int main()
{
list_f *h=NULL;
srand(time(NULL));
h=reclist(h);
//printlist(h);
selection_sort(h);
//printlist(h);
freelist(h);
return 0;
}

list_f *reclist(list_f *h){
	if((h=malloc(sizeof(list_f)))&&(i!=N)){
		h->x=rand()%(N*100)+1;
		i++;
		h->next=reclist(h->next);		
	}else
		h=NULL;
	return h;				
}

void printlist(list_f *h){
	if(h){
		printf("\n%d",h->x);
		return printlist(h->next);		
	}return;
}

void freelist(list_f *h){
	if(h){
		freelist(h->next);
		free(h);
	}return;
}

void selection_sort(list_f *h){
	list_f *temp=NULL,*min=NULL;
	int tmp;
	if(h->next){
		min=h;
		for(temp=h->next;temp;temp=temp->next){
			if(temp->x < min->x)
				min=temp;
		}
		if(min!=h){
			tmp=h->x;
			h->x=min->x;
			min->x=tmp;
		}
		selection_sort(h->next);	
	}return;
}
