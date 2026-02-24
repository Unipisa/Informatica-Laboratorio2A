#include <stdio.h>
#include <threads.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <stdlib.h>

atomic_int thread_attivi = 0;

int thread_func(void *arg)
{
	int id = *(int *)arg;				// recupera l'id del thread
	int tempo_rnd = 1 + (rand() % 4);	// genera un tempo casuale tra 1 e 4 secondi
	printf("Inizio Thread: %d,"
			"resterà attivo per "
			"%d sec\n", id, tempo_rnd);	// stampa l'inizio del thread
	
	struct timespec ts = 
		{ .tv_sec = tempo_rnd, .tv_nsec = 0 };	// imposta il tempo di attesa
	thrd_sleep(&ts, NULL);						// attende il tempo impostato
	printf("Fine Thread: %d\n", id);			// stampa la fine del thread
	atomic_fetch_sub(&thread_attivi, 1);
	return 0;
}

int main()
{
	const int N = 5;		// numero di thread
	thrd_t threads[N];		// array di thread
	int thread_ids[] =	
		{0, 1, 2, 3, 4};	// array di id dei thread

	for (int i = 0; i < N; i++)	
	{
		thrd_create(		// crea un thread
			&threads[i],	// id del thread
			thread_func,	// funzione del thread
			&thread_ids[i]	// argomento della funzione
		);

		atomic_fetch_add(&thread_attivi, 1);

		thrd_detach(threads[i]);	// imposta il thread i come detached
									// il thread non deve essere esplicitamente 
									// terminato il sistema operativo si occupa 
									// di liberare le risorse allocate
	}

	for (int i = 0; i < N; i++)
	{
		int ret = thrd_join(threads[i], NULL);	// attende la terminazione del thread i
		if (ret == thrd_success) {				// verifica il risultato del join
			printf("Thread %d terminato correttamente.\n", i); 	
		} else {
			printf("Errore nel join del thread %d\n", i);
		}
	}

	#ifdef BARRIER
		while (atomic_load(&thread_attivi) > 0)
		{
			printf("Thread attivi: %d\n", atomic_load(&thread_attivi));
			struct timespec ts = 
				{ .tv_sec = 0, .tv_nsec = 5.0e8 };	// imposta il tempo di attesa (0.5 secondi)
			thrd_sleep(&ts, NULL);					// attende il tempo impostato
		}
	#endif

	printf("Termine Programma.\n");
	return 0;
}