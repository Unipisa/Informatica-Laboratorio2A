// Esempio di una Map() fatta con i thread C11, che fa più elaborazioni

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <stdatomic.h>
#include <time.h>

#define N 5
#define M 10

mtx_t mtx;
cnd_t cnd;

int input_data[M][N];

typedef struct main_data {
	int elemento;
	int (*f)(int);
} main_data_t;
main_data_t thread_data[N];

int iterazione = 0;
void nuovi_dati_ai_thread() {
	for (int i = 0; i < N; i++) {
		input_data[iterazione-1][i] = thread_data[i].elemento;
		thread_data[i].elemento = input_data[iterazione][i];
	}
	iterazione++;
}

int count = 0;
void barrier() {
	mtx_lock(&mtx);
	count++;
	if (count == N) {
		count = 0;
		nuovi_dati_ai_thread();
		stampa_matrice("\nRisultati in output nella barrier", input_data, M, N);
		cnd_broadcast(&cnd);
		mtx_unlock(&mtx);
	} else {
		cnd_wait(&cnd, &mtx);
		mtx_unlock(&mtx);
	}
}

void stampa(char * premessa, main_data_t * data, int n) {
	printf("%s: ", premessa);
	for (int i = 0; i < n; i++) {
		printf("%d, ", data[i].elemento);
	}
	printf("\n");
}

void stampa_matrice(char * premessa, int data[M][N], int m, int n) {
	printf("%s: \n", premessa);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d, ", data[i][j]);
		}
		printf("\n");
	}
	printf(" ----- \n");
}

int quadrato (int i){ return i*i; }

int map(void * arg) {

	main_data_t * input = (main_data_t *) arg;
	int (*f)(int) = input->f;

	do {
		int data = input->elemento;

		// Calcolo della funzione
		input->elemento = f(data);

		stampa("Ho elaborato, mi metto in attesa", input, 1);

		// Attesa alla barriera
		barrier();
	} while (iterazione < M);

	return thrd_success;
}

int main() {

	// Inizializzazioni
	srand(time(NULL));
	mtx_init(&mtx, mtx_plain);
	cnd_init(&cnd);
	
	// Inizializzazione dell'array di dati in input
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			input_data[i][j] = rand() % 100;
		}
	}
	stampa_matrice("Elementi in input", input_data, M, N);

	for (int i = 0; i < N; i++) {
		thread_data[i].elemento = input_data[iterazione][i];
		thread_data[i].f = quadrato;
	}
	iterazione = 1;

	thrd_t threads[N];
	// Creazione dei thread
	for (int i = 0; i < N; i++) {
		thrd_create(&threads[i], map, &thread_data[i]);
	}

	// Attesa dei thread
	for (int i = 0; i < N; i++)	{
		thrd_join(threads[i], NULL);
	}
	stampa_matrice("\nRisultati in output", input_data, M, N);

	// Deallocazione delle risorse
	mtx_destroy(&mtx);
	cnd_destroy(&cnd);

	return 0;
}