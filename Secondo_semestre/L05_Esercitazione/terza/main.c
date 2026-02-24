#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

typedef struct {
    int tid;
    long iters;
    int use_mutex;
} arg_t;

static long counter = 0;
static mtx_t m;

int inc_worker(void *arg_) {
    arg_t *a = (arg_t *)arg_;
    for (long i = 0; i < a->iters; i++) {
        if (a->use_mutex) mtx_lock(&m);
        counter++;
        if (a->use_mutex) mtx_unlock(&m);
    }
    return 0;
}

int main(int argc, char **argv) {
    int T = (argc > 1) ? atoi(argv[1]) : 4;
    long K = (argc > 2) ? atol(argv[2]) : 1000000L;
    int use_mutex = (argc > 3) ? atoi(argv[3]) : 1; // 1=mutex, 0=NO mutex

    if (use_mutex) {
        if (mtx_init(&m, mtx_plain) != thrd_success) {
            fprintf(stderr, "mtx_init failed\n");
            return 1;
        }
    }

    thrd_t *threads = malloc((size_t)T * sizeof(thrd_t));
    arg_t *args = malloc((size_t)T * sizeof(arg_t));
    if (!threads || !args) return 2;

    counter = 0;

    for (int i = 0; i < T; i++) {
        args[i].tid = i;
        args[i].iters = K;
        args[i].use_mutex = use_mutex;
        if (thrd_create(&threads[i], inc_worker, &args[i]) != thrd_success) {
            fprintf(stderr, "thrd_create failed\n");
            return 3;
        }
    }
    for (int i = 0; i < T; i++) thrd_join(threads[i], NULL);

    printf("T=%d K=%ld expected=%ld got=%ld (mutex=%d)\n",
           T, K, (long)T * K, counter, use_mutex);

    if (use_mutex) mtx_destroy(&m);
    free(args);
    free(threads);
    return 0;
}
