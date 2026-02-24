#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

#define ITERATION 5

atomic_flag lock = ATOMIC_FLAG_INIT; 						    // inizializzazione statica
struct timespec ts = { .tv_sec = 1, .tv_nsec = 0 };			    // 1 secondo
double val = 0.0;											    // variabile condivisa		

void spinlock(){ while (atomic_flag_test_and_set(&lock)); }	    // spinlock
void spinunlock(){ atomic_flag_clear(&lock); }				    // rilascio spinlock

void loop_che_perde_tempo(int sec){
	time_t start = time(NULL);									// tempo iniziale
	while (time(NULL) - start < sec)							// per sec secondi
		for (int i = 0; i < 1000000; i++) val += 1.0 / (i + 1); // aggiungo un po' di lavoro a caso
}

int thread_func(void *arg){
	for (size_t i = 0; i < ITERATION; i++){						// per ITERATION volte
		spinlock();												// acquisisco spinlock		
			int id = *(int *)arg;								// leggo l'id del thread
			printf("Thread %d si mette a dormire.\n", id);		
			loop_che_perde_tempo(1);							// lavoro di 1 secondo
			printf("Thread %d si e svegliato\n\n", id);
		spinunlock();											// rilascio spinlock
		thrd_sleep(&ts, NULL);									// dormo per 1 secondo
	}
	return thrd_success;
}

int main(){
	const int N = 5;												// numero di thread
	thrd_t threads[N];												// array di thread					
	int thread_ids[] =	{0, 1, 2, 3, 4};							// id dei thread

	for (int i = 0; i < N; i++)	{
		thrd_create( &threads[i], thread_func, &thread_ids[i] );	// creo i thread
	}

	for (int i = 0; i < N; i++)	{
		int ret = thrd_join(threads[i], NULL);						// aspetto la fine dei thread
		if (ret == thrd_success) printf("Thread %d terminato correttamente.\n", i);		
		else printf("Errore nel join del thread %d\n", i);
	}

	printf("Termine. Valore calcolato: %f\n", val);					
	return 0;
}