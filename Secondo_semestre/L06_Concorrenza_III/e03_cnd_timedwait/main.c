#include <stdio.h>
#include <threads.h>
#include <time.h>

mtx_t mutex;
cnd_t cond;
int pacco_arrivato = 0;

int aspetta_pacco(void *arg) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    ts.tv_sec += 5;  // Timeout di 5 secondi

    mtx_lock(&mutex);
    while (!pacco_arrivato) {
        if (cnd_timedwait(&cond, &mutex, &ts) == thrd_timedout) {
            printf("😭 Il corriere non è arrivato, vado via...\n");
            mtx_unlock(&mutex);
            return thrd_success;
        }
    }
    printf("📦 Evviva, ho ricevuto il pacco!\n");
    mtx_unlock(&mutex);
    return thrd_success;
}

int consegna_pacco(void *arg) {
    thrd_sleep(&(struct timespec){.tv_sec = 3}, NULL);  // Simula ritardo del corriere
    mtx_lock(&mutex);
    pacco_arrivato = 1;
    cnd_signal(&cond);
    mtx_unlock(&mutex);
    return thrd_success;
}

int main() {
    mtx_init(&mutex, mtx_plain);
    cnd_init(&cond);

    thrd_t t1, t2;
    thrd_create(&t1, aspetta_pacco, NULL);
    thrd_create(&t2, consegna_pacco, NULL);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);

    cnd_destroy(&cond);
    mtx_destroy(&mutex);
    return 0;
}
