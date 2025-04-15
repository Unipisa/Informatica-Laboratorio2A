typedef struct nodo_lista {
	int value;
	struct nodo_lista *prossimo;
} nodo_lista_t;

typedef struct lista {
	nodo_lista_t *head;
	nodo_lista_t *tail;
	size_t numero_elementi;
	size_t capienza_massima;
} lista_t;

void push(lista_t *lista, int value);
int pop(lista_t *lista);
void pop_selettiva(lista_t *lista, int value);

void rimuovi_da_lista(lista_t *lista, int value);
void stampa_lista(lista_t *lista);
void inizializa_lista(lista_t *lista, int capienza_massima);
void stampa_report(lista_t *lista);