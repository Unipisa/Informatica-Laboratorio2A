#include <stdio.h>
#include <stdlib.h>

typedef struct SNode {
    int value;
    struct SNode *next;
} SNode;

typedef struct { SNode *head; } IntStack;

void st_init(IntStack *s){ s->head = NULL; }

int  st_is_empty(const IntStack *s){ return s->head == NULL; }

int st_push(IntStack *s, int x){
    SNode *n = malloc(sizeof (SNode)); 
	if (!n) return -1;
    n->value = x; 
	n->next = s->head; 
	s->head = n;
	return 0;
}

int  st_pop (IntStack *s){
    if (st_is_empty(s)) return -1;
    SNode *t = s->head; 
	int v = t->value; 
	s->head = t->next; 
	free(t); 
	return v;
}

void st_free(IntStack *s){
    while (s->head){ 
		SNode *t = s->head; 
		s->head = t->next; 
		free(t); 
	}
}

int main(void){
    IntStack s; st_init(&s);
    for (int i=1;i<=5;++i) st_push(&s, i);
    while (!st_is_empty(&s)) printf("%d ", st_pop(&s));
    printf("\n");
    st_free(&s);
    return 0;
}

