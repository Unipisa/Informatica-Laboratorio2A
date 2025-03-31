#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

#define N_THREADS 4
#define N_INCREMENTS 1000000

atomic_int counter = 0;

int increment(void *arg) {

	/* FRAMMENTO DI CODICE #1 -- INIZIO */
	int increment = (*(int *)arg) %2 == 0 ? 1 : -1;

	for (int i = 0; i < N_INCREMENTS; i++) {
		atomic_fetch_add(&counter, increment);
	}
	return 0;
	/* FRAMMENTO DI CODICE #1 -- FINE */
}

int main() {
	thrd_t threads[N_THREADS];

	/* FRAMMENTO DI CODICE #2 -- INIZIO */
	int idx[N_THREADS];

	for (int i = 0; i < N_THREADS; i++) {
		idx[i] = i;
		thrd_create(&threads[i], increment, &idx[i]);
	}
	for (int i = 0; i < N_THREADS; i++) {
		thrd_join(threads[i], NULL);
	}
	printf("Counter: %d\n", counter);
	/* FRAMMENTO DI CODICE #2 -- FINE */
	
	return 0;
}