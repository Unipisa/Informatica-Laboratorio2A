#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

#include "lista.h"
#include "spinlock.h"


void inserisci_in_coda(lista_t *lista, int value) {
	nodo_lista_t *nodo = malloc(sizeof(nodo_lista_t));
	nodo->value = value;
	nodo->prossimo = NULL;

	if (lista->head == NULL) {
		lista->head = nodo;
		lista->tail = nodo;
	} else {
		lista->tail->prossimo = nodo;
		lista->tail = nodo;
	}
	lista->lunghezza++;
}

void rimuovi_da_lista(lista_t *lista, int value) {
	nodo_lista_t *nodo = lista->head;
	nodo_lista_t *precedente = NULL;

	while (nodo != NULL) {
		if (nodo->value == value) {
			if (precedente == NULL) {
				lista->head = nodo->prossimo;
			} else {
				precedente->prossimo = nodo->prossimo;
			}
			if (nodo == lista->tail) {
				lista->tail = precedente;
			}
			free(nodo);
			lista->lunghezza--;
			return;
		}
		precedente = nodo;
		nodo = nodo->prossimo;
	}
}

void stampa_lista(lista_t *lista) {
	nodo_lista_t *nodo = lista->head;

	while (nodo != NULL) {
		printf("%d ", nodo->value);
		nodo = nodo->prossimo;
	}
	printf("\n");
}

// stampa un report della lista indicando quanti elementi contiene per ogni numero diverso
void stampa_report(lista_t *lista) {
	nodo_lista_t *nodo = lista->head;
	int *contatori = calloc(lista->lunghezza, sizeof(int));
	int *valori = calloc(lista->lunghezza, sizeof(int));
	int i = 0;

	while (nodo != NULL) {
		int j = 0;
		while (j < i && valori[j] != nodo->value) j++;
		if (j == i) {
			valori[i] = nodo->value;
			i++;
		}
		contatori[j]++;
		nodo = nodo->prossimo;
	}

	printf("\nReport:\n");
	for (int j = 0; j < i; j++) {
		printf("Numero istanze di %d: %d\n", valori[j], contatori[j]);
	}
	free(contatori);
	free(valori);
}


void inizializa_lista(lista_t *lista) {
	lista->head = NULL;
	lista->tail = NULL;
	lista->lunghezza = 0;
}
