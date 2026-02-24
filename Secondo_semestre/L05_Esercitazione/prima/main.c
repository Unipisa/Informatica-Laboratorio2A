#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

typedef struct {
    int id;
    int ms;
} thread_arg_t;

static void sleep_ms(long ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;
    thrd_sleep(&ts, NULL);
}

int worker(void *arg_) {
    thread_arg_t *arg = (thread_arg_t *)arg_;
    printf("T%d: start\n", arg->id);
    sleep_ms(arg->ms);
    printf("T%d: end\n", arg->id);
    return arg->id * 10;
}

int main(int argc, char **argv) {
    int N = (argc > 1) ? atoi(argv[1]) : 4;

    thrd_t *threads = malloc((size_t)N * sizeof(thrd_t));
    thread_arg_t *args = malloc((size_t)N * sizeof(thread_arg_t));
    if (!threads || !args) {
        fprintf(stderr, "alloc failed\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        args[i].id = i;
        args[i].ms = 100 + (i * 150);
        if (thrd_create(&threads[i], worker, &args[i]) != thrd_success) {
            fprintf(stderr, "thrd_create failed on %d\n", i);
            return 2;
        }
    }

    for (int i = 0; i < N; i++) {
        int rc = 0;
        if (thrd_join(threads[i], &rc) != thrd_success) {
            fprintf(stderr, "thrd_join failed on %d\n", i);
            return 3;
        }
        printf("joined T%d -> rc=%d\n", i, rc);
    }

    printf("all joined\n");
    free(args);
    free(threads);
    return 0;
}
