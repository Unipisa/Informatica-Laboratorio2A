#include <stdio.h>
#include <threads.h>
#include <time.h>

mtx_t macchina_caffe_lock;

int fai_caffe(void *arg) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    ts.tv_sec += 4;  // Aspetta massimo 2 secondi

	char* nome = (char*)arg;

	printf("[%s] Sono arrivato in cucina...\n", nome);

    if (mtx_timedlock(&macchina_caffe_lock, &ts) == thrd_success) {
        printf("[%s] ☕ Sto facendo un caffè...\n", nome);
        thrd_sleep(&(struct timespec){.tv_sec = 3}, NULL);  // Tempo per preparare il caffè
        printf("[%s] 😌 Caffè pronto! Libero la macchina.\n", nome);
        mtx_unlock(&macchina_caffe_lock);
    } else {
        printf("[%s] 😖 La macchina è occupata, cerco un altro distributore...\n", nome);
    }
	return thrd_success;
}

int main() {
    mtx_init(&macchina_caffe_lock, mtx_plain);

	char * nomi[] = 
		{"Pippo", "Pluto"};	// Nomi dei caffeinomani

    thrd_t t1, t2;
    thrd_create(&t1, fai_caffe, nomi[0]);
    thrd_create(&t2, fai_caffe, nomi[1]);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);

    mtx_destroy(&macchina_caffe_lock);
    return 0;
}
