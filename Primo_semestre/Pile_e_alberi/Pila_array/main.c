#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 8

typedef struct {
    int *data;
    size_t size, cap;
} IntStack;

void st_init(IntStack *s) {
    s->size = 0; 
	s->cap = CAPACITY;
    s->data = (int *) malloc(CAPACITY * sizeof(int));
}

int  st_is_empty(IntStack *s) { return s->size == 0; }

void st_free (IntStack *s) { free(s->data); s->data = NULL; s->size = s->cap = 0; }

int st_push(IntStack *s, int x) {
    if (s->size == s->cap) {
		return -1;
    }
    s->data[s->size++] = x;
	return 0;
}
int st_pop(IntStack *s) {

    if (st_is_empty(s)) return -1;
    return s->data[--s->size];
}
int st_top(IntStack *s) {

    if (st_is_empty(s)) return -1;
    return s->data[s->size - 1];
}

int main(void) {
    IntStack s; st_init(&s);
    for (int i = 1; i <= 5; ++i) st_push(&s, i*10);
    printf("Top=%d\n", st_top(&s));
    while (!st_is_empty(&s)) printf("%d ", st_pop(&s));
    printf("\n");
    st_free(&s);
    return 0;
}
