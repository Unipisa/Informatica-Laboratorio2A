typedef struct nodo_lista {
	int value;
	struct nodo_lista *prossimo;
} nodo_lista_t;

typedef struct lista {
	nodo_lista_t *head;
	nodo_lista_t *tail;
	size_t lunghezza;
} lista_t;

void inserisci_in_coda(lista_t *lista, int value);
void rimuovi_da_lista(lista_t *lista, int value);
void stampa_lista(lista_t *lista);
void inizializa_lista(lista_t *lista);
void stampa_report(lista_t *lista);