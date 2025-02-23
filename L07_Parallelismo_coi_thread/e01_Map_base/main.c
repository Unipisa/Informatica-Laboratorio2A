// Esempio base di una Map() fatta con i thread C11

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <stdatomic.h>
#include <time.h>

#define N 5

typedef struct main_data {
	int elemento;
	int (*f)(int);
} main_data_t;
main_data_t data[N];

mtx_t mtx;
cnd_t cnd;

void stampa(char * premessa, main_data_t * data, int n) {
	printf("%s: ", premessa);
	
	for (int i = 0; i < n; i++) {
		printf("%d, ", data[i].elemento);
	}
	
	printf("\n");
}

int count = 0;
void barrier() {
	mtx_lock(&mtx);
	count++;
	if (count == N) {
		count = 0;
		cnd_broadcast(&cnd);
		mtx_unlock(&mtx);
	} else {
		cnd_wait(&cnd, &mtx);
		mtx_unlock(&mtx);
	}
}

int quadrato (int i){ return i*i; }

int map(void * arg) {

	main_data_t * input = (main_data_t *) arg;
	int (*f)(int) = input->f;
	int data = input->elemento;

	// Calcolo della funzione
	input->elemento = f(data);

	stampa("Ho elaborato, mi metto in attesa", input, 1);

	// Attesa alla barriera
	barrier();

	return thrd_success;
}

int main() {
	thrd_t threads[N];

	// Inizializzazione del generatore di numeri pseudo-casuali
	srand(time(NULL));

	mtx_init(&mtx, mtx_plain);
	cnd_init(&cnd);
	
	// Inizializzazione dell'array di strutture
	for (int i = 0; i < N; i++) {
		data[i].elemento = rand() % 100;
		data[i].f = quadrato;
	}

	stampa("Elementi in input", data, N);

	// Creazione dei thread
	for (int i = 0; i < N; i++) {
		thrd_create(&threads[i], map, &data[i]);
	}

	// Attesa dei thread
	for (int i = 0; i < N; i++)	{
		thrd_join(threads[i], NULL);
	}

	stampa("Risultati in output", data, N);

	// Deallocazione delle risorse
	mtx_destroy(&mtx);
	cnd_destroy(&cnd);

	return 0;
}