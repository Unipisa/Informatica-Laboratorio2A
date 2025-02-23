#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <time.h>

#define NUM_CUOCHI 5

mtx_t fornello;  // Mutex per il controllo del fornello

// Funzione eseguita dai thread (cuochi che cucinano)
int cucina(void *arg) {
    int id = *(int *)arg;

    printf("👨‍🍳 Cuoco %d è pronto a cucinare.\n", id);

    // Ogni cuoco prova a usare il fornello
    mtx_lock(&fornello);  // Se un altro cuoco è già dentro, aspetta
    printf("🔥 Cuoco %d sta usando il fornello!\n", id);
    
    // Simula la cottura del piatto
    thrd_sleep(&(struct timespec){.tv_sec=(1)}, NULL);
	
    printf("✅ Cuoco %d ha finito di cucinare.\n", id);
    mtx_unlock(&fornello);  // Libera il fornello per gli altri

    return 0;
}

int main() {
    srand(time(NULL));

    thrd_t threads[NUM_CUOCHI];
    int id[NUM_CUOCHI];

    // Inizializza il mutex
    mtx_init(&fornello, mtx_plain);

    // Crea i thread (i cuochi)
    for (int i = 0; i < NUM_CUOCHI; i++) {
        id[i] = i + 1;
        thrd_create(&threads[i], cucina, &id[i]);
    }

    // Aspetta che tutti i cuochi terminino
    for (int i = 0; i < NUM_CUOCHI; i++) {
        thrd_join(threads[i], NULL);
    }

    printf("🍽 Tutti i cuochi hanno finito di cucinare!\n");

    // Distrugge il mutex
    mtx_destroy(&fornello);

    return 0;
}
