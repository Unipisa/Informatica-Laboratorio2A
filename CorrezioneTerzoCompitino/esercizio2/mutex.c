#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

#define N_THREADS 4
#define N_INCREMENTS 1000000

int counter = 0;
mtx_t mtx;

int increment(void *arg) {

	/* FRAMMENTO DI CODICE #1 -- INIZIO */
	int increment = (*(int *)arg) %2 == 0 ? 1 : -1;

	for (int i = 0; i < N_INCREMENTS; i++) {
		mtx_lock(&mtx);
		counter += increment;
		mtx_unlock(&mtx);
	}
	return 0;
	/* FRAMMENTO DI CODICE #1 -- FINE */
}

int main() {
	thrd_t threads[N_THREADS];

	/* FRAMMENTO DI CODICE #2 -- INIZIO */
	int idx[N_THREADS];
	mtx_init(&mtx, mtx_plain);

	for (int i = 0; i < N_THREADS; i++) {
		idx[i] = i;
		thrd_create(&threads[i], increment, &idx[i]);
	}
	for (int i = 0; i < N_THREADS; i++) {
		thrd_join(threads[i], NULL);
	}
	printf("Counter: %d\n", counter);
	mtx_destroy(&mtx);
	/* FRAMMENTO DI CODICE #2 -- FINE */
	
	return 0;
}