#include <stdio.h>
#include <threads.h>

#define N 5 // numero di thread

int thread_func(void *arg)
{
	thrd_t id_ricevuto = *(thrd_t *)arg;	// recupera l'id del thread 
	thrd_t id_calcolato = thrd_current();	// recupera l'id del thread
	printf("Thread ID ric: %lu\n", id_ricevuto);	// stampa l'ID del thread
	printf("Thread ID cal: %lu\n", id_calcolato);	// stampa l'ID del thread
	return thrd_success;		// ritorna il valore di successo
}

int main()
{	
	thrd_t threads[N];		// array descrittori dei thread

	for (int i = 0; i < N; i++){
		thrd_create(		// crea un thread
			&threads[i],	// id del thread
			thread_func,	// funzione del thread
			&threads[i]		// argomento della funzione
		);
	}

	for (int i = 0; i < N; i++) {
		thrd_t ret = thrd_join(threads[i], NULL);	// attende la terminazione del thread i
		if (ret == thrd_success)				// verifica il risultato del join
			printf("Thread con ID: %lu terminato correttamente.\n", threads[i]); 	
		else
			printf("Errore nel join del thread %d\n", i);
	}

	return 0;
}