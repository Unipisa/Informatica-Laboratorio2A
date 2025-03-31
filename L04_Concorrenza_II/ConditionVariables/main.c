#include<threads.h>
#include<stdio.h>
#include<stdlib.h>

#include "lista.h"

#define DEBUG
#define ITERAZIONI 3
#define NUMERO_PRODUTTORI 5
#define NUMERO_CONSUMATORI 5
#define SLOT_LISTA 2

mtx_t mutex;
cnd_t lista_vuota;
cnd_t lista_piena;
lista_t lista;

int produttore(void * arg){
	int produzioni = 0;
	do {
	
		mtx_lock(&mutex);
			#ifdef DEBUG   
				printf("Produttore %lu\n", thrd_current()); 
			#endif

			if (lista.numero_elementi < lista.capienza_massima)
			{
				push(&lista, produzioni);
				produzioni++;
				if (lista.numero_elementi == 1){
					cnd_broadcast(&lista_vuota);
				}
				
				#ifdef DEBUG   
					printf("Elemento %d inserito\n", (produzioni-1));
				#endif
			
			} else{
				while (lista.numero_elementi == lista.capienza_massima) {
					
					#ifdef DEBUG 
						printf("Lista piena\n");
					#endif
					
					cnd_wait(&lista_piena, &mutex);
				}
			}

		mtx_unlock(&mutex);
	
	} while (produzioni < ITERAZIONI);
	
	return thrd_success;
}

int consumatore (void * arg){
	int consumazioni = 0;
	do {
		mtx_lock(&mutex);

			#ifdef DEBUG   
				printf("Consumatore %lu\n", thrd_current());
			#endif
		
			if (lista.numero_elementi > 0) {
				int item = pop(&lista);
				consumazioni++;
				if (lista.numero_elementi == (lista.capienza_massima - 1)){
					cnd_broadcast(&lista_piena);
				}
				
				#ifdef DEBUG  
					printf("Elemento %d rimosso\n", item);
				#endif
		
			} else {
				while (lista.numero_elementi == 0) {
		
					#ifdef DEBUG 
						printf("Lista vuota\n");
					#endif
		
					cnd_wait(&lista_vuota, &mutex);
				}
			}
		
		mtx_unlock(&mutex);
	} while (consumazioni < ITERAZIONI);

	return thrd_success;
}

void inizializza_mutex(mtx_t *mutex){
	if (mtx_init(mutex, mtx_plain) != thrd_success) {
		fprintf(stderr, "Errore inizializzazione mutex.\n");
		exit(1);
	}
}

void distruggi_mutex(mtx_t *mutex){
	mtx_destroy(mutex);
}

void inizializza_cnt(cnd_t *cond){
	if (cnd_init(cond) != thrd_success) {
		fprintf(stderr, "Errore inizializzazione variabile di condizione.\n");
		exit(1);
	}
}

void distruggi_cnt(cnd_t *cond){
    cnd_destroy(cond);
}

int main(){
	thrd_t produttori[NUMERO_PRODUTTORI];
	thrd_t consumatori[NUMERO_CONSUMATORI];

	inizializa_lista(&lista, SLOT_LISTA);
	inizializza_mutex(&mutex);
	inizializza_cnt(&lista_vuota);
	inizializza_cnt(&lista_piena);

	for (int i = 0; i < NUMERO_PRODUTTORI; i++) {
		thrd_create(&produttori[i], produttore, NULL);
	}

	for (int i = 0; i < NUMERO_CONSUMATORI; i++) {
		thrd_create(&consumatori[i], consumatore, NULL);
	}

	for (int i = 0; i < NUMERO_PRODUTTORI; i++) {
		thrd_join(produttori[i], NULL);
	}

	for (int i = 0; i < NUMERO_CONSUMATORI; i++) {
		thrd_join(consumatori[i], NULL);
	}

	//stampa_report(&lista);
	distruggi_mutex(&mutex);
	distruggi_cnt(&lista_vuota);
	distruggi_cnt(&lista_piena);

	return 0;
}