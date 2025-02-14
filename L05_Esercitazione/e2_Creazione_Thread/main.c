// L'idea è simulare una corsa tra conigli usando thread:
// Ogni coniglio è un thread che "corre" avanzando casualmente.
// La funzione thrd_join permette di aspettare che tutti i conigli finiscano la corsa.
// Vince il coniglio che raggiunge per primo il traguardo!

// Utilizziamo una variabile atomica (atomic_bool) per controllare la partenza:

// Ogni thread inizia con un while(!via) {} che lo tiene in attesa.
// Il main thread imposta via = true quando tutti i conigli sono pronti.

#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <threads.h>
#include <time.h>
#include <stdbool.h>

#define NUM_CONIGLI 5
#define TRAGUARDO 50

typedef struct {
    int id;
    int distanza;
} Coniglio;

atomic_bool via = false;  // Variabile atomica per la partenza sincronizzata

// Funzione eseguita dai thread (simula la corsa)
int gara_coniglio(void *arg) {
    Coniglio *c = (Coniglio *)arg;

    // Attende il via
    while (!via) {}  // Busy-wait minima, parte nello stesso istante per tutti

    // Gara vera e propria
    while (c->distanza < TRAGUARDO) {
        int passo = rand() % 5 + 1;  // Avanza di 1-5 passi casualmente
        c->distanza += passo;
        printf("Coniglio %d ha corso fino a %d\n", c->id, c->distanza);
        thrd_sleep(&(struct timespec){0, 200000000L}, NULL); // Pausa 200ms
    }

    printf("🐰 Coniglio %d ha tagliato il traguardo!\n", c->id);
    return 0;
}

int main() {
    srand(time(NULL));

    thrd_t threads[NUM_CONIGLI];
    Coniglio conigli[NUM_CONIGLI];

    // Creazione dei thread
    for (int i = 0; i < NUM_CONIGLI; i++) {
        conigli[i].id = i + 1;
        conigli[i].distanza = 0;
        thrd_create(&threads[i], gara_coniglio, &conigli[i]);
    }

    // Sincronizzazione: aspetta un attimo e poi dà il via
    thrd_sleep(&(struct timespec){0, 500000000L}, NULL); // Pausa 500ms
    printf("🏁 VIA!\n");
    via = true;  // I thread leggono questa variabile e partono simultaneamente

    // Aspetta che tutti i conigli terminino
    for (int i = 0; i < NUM_CONIGLI; i++) {
        thrd_join(threads[i], NULL);
    }

    printf("🎉 La gara è finita! Complimenti al vincitore!\n");

    return 0;
}
