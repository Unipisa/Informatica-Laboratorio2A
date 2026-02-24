#include <stdio.h>
#include <threads.h>

#define N 5 // numero di thread

thrd_t t_annidato;

int thread_func_annidato(void *arg)
{
	printf("Entro nel Thread INTERNO\n");	
	thrd_sleep(&(struct timespec){.tv_sec=3}, NULL);	// dorme per 1 secondo
	printf("Esco dal Thread INTERNO\n");	
	return thrd_success;		// ritorna il valore di successo
}


int thread_func(void *arg)
{
	printf("Thread ESTERNO\n");			// stampa il nome del thread

	thrd_create(		// crea un thread
		&t_annidato,		// id del thread
		thread_func_annidato,	// funzione del thread
		NULL			// argomento della funzione
	);

	// thrd_t ret = thrd_join(t_annidato, NULL);	
	// if (ret == thrd_success)				
	// 	printf("Thread con ID: %lu terminato correttamente.\n", t_annidato); 	
	// else
	// 	printf("Errore nel join del thread %lu\n", ret);

	printf("Esco dal Thread ESTERNO\n");
	return thrd_success;		// ritorna il valore di successo
}

int main()
{	
	thrd_t thread;		// array descrittori dei thread

	thrd_create(		// crea un thread
		&thread,		// id del thread
		thread_func,	// funzione del thread
		NULL			// argomento della funzione
	);
	
	thrd_t ret = thrd_join(thread, NULL);	
	if (ret == thrd_success)				
		printf("Thread con ID: %lu terminato correttamente.\n", thread); 	
	else
		printf("Errore nel join del thread %lu\n", ret);
	

	ret = thrd_join(t_annidato, NULL);	
	if (ret == thrd_success)				
		printf("Thread con ID: %lu terminato correttamente.\n", t_annidato); 	
	else
		printf("Errore nel join del thread %lu\n", ret);

	return 0;
}