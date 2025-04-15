#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

atomic_int flag = 0;
int shared_data = 0;

int writer(void *arg) {
    for (int i = 1; i <= 5; i++) {
        shared_data = i;
        printf("Writer: scritto %d\n", i);
        atomic_store(&flag, 1);

        // Attende che il reader legga, cedendo il controllo della CPU
        while (atomic_load(&flag) == 1)
            thrd_yield();  // Permette ad altri thread di girare
    }
    return 0;
}

int reader(void *arg) {
    for (int i = 1; i <= 5; i++) {
        while (atomic_load(&flag) == 0)
            thrd_yield();  // Evita di monopolizzare la CPU

        printf("Reader: letto %d\n", shared_data);
        atomic_store(&flag, 0);
    }
    return 0;
}

int main() {
    thrd_t t1, t2;
    thrd_create(&t1, writer, NULL);
    thrd_create(&t2, reader, NULL);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);
    return 0;
}
