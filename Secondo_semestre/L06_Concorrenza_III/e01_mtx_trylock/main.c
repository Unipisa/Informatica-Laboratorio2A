#include <stdio.h>
#include <threads.h>
#include <stdlib.h>

#define FETTE 6								// Numero di fette in cui si divide la pizza
#define TESISTI 3							// Numero di tesisti

mtx_t frigo;								// Mutex per il frigo
int fette_pizza = FETTE;					// Numero di fette di pizza nel frigo

int prendi_pizza(void * arg) {				// Funzione del thread per prendere una fetta di pizza

	int fame = 1 + rand() % 3;				// Numero di fette di pizza che il tesista vuole mangiare

	printf("[%s] Ho fame, vado"
		   " in cerca di Pizza...\n", 		// Stampa a video
		   (char *)arg
	);

	do {
		if (mtx_trylock(&frigo) == thrd_success) {	// Se ottengo il lock sul frigo
			if (fette_pizza > 0) {
				--fette_pizza;						// Prendo una fetta di pizza
				--fame;								// Decremento il numero di fette che voglio mangiare

				printf("[%s] Ho preso una fetta "	// Stampa a video
					   "di pizza! Rimaste: %d\n", 
					   (char *)arg, fette_pizza	
				);

				thrd_sleep(	&(struct timespec)		// Simula il tempo di mangiare
							{.tv_sec = 2}, NULL
				);
			
			} else {
				printf(	"[%s] La pizza è finita, "	// Stampa a video
						"che tristezza!\n", 
						(char *)arg
				);

				mtx_unlock(&frigo);					// Rilascio il lock sul frigo se la pizza è finita
				return thrd_success;				// Esco dalla funzione
			}
			mtx_unlock(&frigo);						// Rilascio il lock sul frigo
		} else {
			printf( "[%s] Frigo occupato, "			// Stampa a video
					"torno a lavorare alla "
					"tesi...\n", (char *)arg);

			thrd_sleep(&(struct timespec)			// Simula il tempo di attesa prima di riprovare
			{.tv_sec = 1}, NULL);
		}
	} while (fame > 0);								// Ripeto finché ho fame

	printf(	"[%s] Ho finito di "					// Stampa a video 
			"mangiare!\n", (char *)arg);

	return thrd_success;							// Esco dalla funzione
}

int main() {

	srand(time(NULL));								// Inizializzo il generatore di numeri casuali
	mtx_init(&frigo, mtx_plain);					// Inizializzo il mutex per il frigo

	char * nomi[] = 
		{"Pippo", "Pluto", "Paperino", "Topolino"};	// Nomi dei tesisti
	
	thrd_t t[4];									// Array di descrittori thread

	for (int i = 0; i < TESISTI; i++) {				
	    thrd_create(&t[i], prendi_pizza, nomi[i]);	// Creo i thread
	}

	for (int i = 0; i < TESISTI; i++) {
	    thrd_join(t[i], NULL);						// Attendo i thread
	}

    mtx_destroy(&frigo);							// Distruggo il mutex

    return 0;										
}
