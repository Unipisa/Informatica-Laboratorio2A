#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 20

typedef struct {
    int buffer[BUFFER_SIZE];
    int count;
    int head;
    int tail;
    mtx_t mutex;
    cnd_t not_empty;
    cnd_t not_full;
} queue_t;

void queue_init(queue_t *q) {
    q->count = q->head = q->tail = 0;
    mtx_init(&q->mutex, mtx_plain);
    cnd_init(&q->not_empty);
    cnd_init(&q->not_full);
}

void queue_destroy(queue_t *q) {
    mtx_destroy(&q->mutex);
    cnd_destroy(&q->not_empty);
    cnd_destroy(&q->not_full);
}

void queue_push(queue_t *q, int value) {
    mtx_lock(&q->mutex);
    while (q->count == BUFFER_SIZE) {
        cnd_wait(&q->not_full, &q->mutex);
    }
    q->buffer[q->tail] = value;
    q->tail = (q->tail + 1) % BUFFER_SIZE;
    q->count++;
    cnd_signal(&q->not_empty);
    mtx_unlock(&q->mutex);
}

int queue_pop(queue_t *q) {
    mtx_lock(&q->mutex);
    while (q->count == 0) {
        cnd_wait(&q->not_empty, &q->mutex);
    }
    int value = q->buffer[q->head];
    q->head = (q->head + 1) % BUFFER_SIZE;
    q->count--;
    cnd_signal(&q->not_full);
    mtx_unlock(&q->mutex);
    return value;
}

// Code per i thread
queue_t queue1, queue2;

int generator(void *arg) {
    for (int i = 1; i <= NUM_ITEMS; i++) {
        queue_push(&queue1, i);
    }
    queue_push(&queue1, -1); // Segnale di fine
    return 0;
}

int processor(void *arg) {
    while (1) {
        int value = queue_pop(&queue1);
        if (value == -1) {
            queue_push(&queue2, -1); // Propaga segnale di fine
            break;
        }
        queue_push(&queue2, value * 2);
    }
    return 0;
}

int printer(void *arg) {
    while (1) {
        int value = queue_pop(&queue2);
        if (value == -1) break;
        printf("Output: %d\n", value);
    }
    return 0;
}

int main() {
    queue_init(&queue1);
    queue_init(&queue2);

    thrd_t t1, t2, t3;
    thrd_create(&t1, generator, NULL);
    thrd_create(&t2, processor, NULL);
    thrd_create(&t3, printer, NULL);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);
    thrd_join(t3, NULL);

    queue_destroy(&queue1);
    queue_destroy(&queue2);

    return 0;
}
