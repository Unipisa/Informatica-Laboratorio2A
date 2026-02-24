#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>
#include <stdlib.h>

#include "spinlock.h"
#include "lista.h"

#define MAX_THREADS 700

#define MUTEX_VERSION

#ifdef MUTEX_VERSION
	mtx_t mutex;
#elif defined(SPINLOCK_VERSION)
	atomic_flag lock = ATOMIC_FLAG_INIT;
#endif

int thread_func(void *arg){
	lista_t *lista = (lista_t *)arg;

	for (size_t i = 0; i < 500; i++) {

	#ifdef MUTEX_VERSION
		mtx_lock(&mutex);
	#elif defined(SPINLOCK_VERSION)
		spinlock(&lock);
	#endif

	inserisci_in_coda(lista, i);


	#ifdef MUTEX_VERSION
		mtx_unlock(&mutex);
	#elif defined(SPINLOCK_VERSION)
		spinunlock(&lock);
	#endif

	}
	return 0;
}

void inizializza_mutex(mtx_t *mutex){
	if (mtx_init(mutex, mtx_plain) != thrd_success) {
		fprintf(stderr, "Errore inizializzazione mutex.\n");
		exit(1);
	}
}

void distruggi_mutex(mtx_t *mutex){
	mtx_destroy(mutex);
}

int main()
{
	thrd_t threads[MAX_THREADS];
	lista_t lista;

	#ifdef MUTEX_VERSION
		inizializza_mutex(&mutex);
	#endif

	inizializa_lista(&lista);

	for (int i = 0; i < MAX_THREADS; i++) thrd_create(&threads[i], thread_func,	&lista);
	for (int i = 0; i < MAX_THREADS; i++) thrd_join(threads[i], NULL);

	stampa_report(&lista);

	#ifdef MUTEX_VERSION
		distruggi_mutex(&mutex);
	#endif

	printf("Termine Programma.\n");
	return 0;
}