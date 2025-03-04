#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

#define M_PRODUTTORI 3
#define N_CONSUMATORI 4
#define K_BUFFER 5

int buffer = 0;  // Numero di bibite nel distributore
mtx_t mutex;
cnd_t pieno, vuoto;

// Funzione produttore
int produttore(void *arg) {
    int id = *(int *)arg;

    while (1) {
        thrd_sleep(&(struct timespec){0, (rand() % 3 + 1) * 500000000L}, NULL);

        mtx_lock(&mutex);
        while (buffer == K_BUFFER) {
            cnd_wait(&pieno, &mutex);  // Aspetta se il buffer è pieno
        }

        buffer++;
        printf("🥤 Produttore %d ha aggiunto una bibita. Totale: %d\n", id, buffer);

        cnd_broadcast(&vuoto);  // Sveglia TUTTI i consumatori
        mtx_unlock(&mutex);
    }

    return 0;
}

// Funzione consumatore
int consumatore(void *arg) {
    int id = *(int *)arg;

    while (1) {
        thrd_sleep(&(struct timespec){0, (rand() % 3 + 1) * 500000000L}, NULL);

        mtx_lock(&mutex);
        while (buffer == 0) {
            cnd_wait(&vuoto, &mutex);  // Aspetta se il buffer è vuoto
        }

        buffer--;
        printf("🚰 Consumatore %d ha preso una bibita. Totale: %d\n", id, buffer);

        cnd_broadcast(&pieno);  // Sveglia TUTTI i produttori
        mtx_unlock(&mutex);
    }

    return 0;
}

int main() {
    srand(time(NULL));

    thrd_t produttori[M_PRODUTTORI];
    thrd_t consumatori[N_CONSUMATORI];
    int id_prod[M_PRODUTTORI], id_cons[N_CONSUMATORI];

    mtx_init(&mutex, mtx_plain);
    cnd_init(&pieno);
    cnd_init(&vuoto);

    // Creazione produttori
    for (int i = 0; i < M_PRODUTTORI; i++) {
        id_prod[i] = i + 1;
        thrd_create(&produttori[i], produttore, &id_prod[i]);
    }

    // Creazione consumatori
    for (int i = 0; i < N_CONSUMATORI; i++) {
        id_cons[i] = i + 1;
        thrd_create(&consumatori[i], consumatore, &id_cons[i]);
    }

    // Attende i thread (in un'app reale, servirebbe una condizione di terminazione)
    for (int i = 0; i < M_PRODUTTORI; i++) {
        thrd_join(produttori[i], NULL);
    }
    for (int i = 0; i < N_CONSUMATORI; i++) {
        thrd_join(consumatori[i], NULL);
    }

    mtx_destroy(&mutex);
    cnd_destroy(&pieno);
    cnd_destroy(&vuoto);

    return 0;
}
