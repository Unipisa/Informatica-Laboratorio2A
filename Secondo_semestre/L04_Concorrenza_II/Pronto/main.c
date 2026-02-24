#include <stdio.h>
#include <threads.h>

mtx_t mutex;
cnd_t cond_var;
int pronto = 0; // La condizione che monitoriamo

int compito_thread(void* arg) {
    mtx_lock(&mutex);
    
    while (pronto == 0) {
        printf("[Thread] Non è ancora pronto, vado a dormire...\n");
        // Rilascia il mutex e dorme. Al risveglio, riprende il mutex.
        cnd_wait(&cond_var, &mutex);
    }
    
    printf("[Thread] Segnale ricevuto! Comincio a lavorare.\n");
    mtx_unlock(&mutex);
    return 0;
}

int main() {
    thrd_t t_id;
    mtx_init(&mutex, mtx_plain);
    cnd_init(&cond_var);

    thrd_create(&t_id, compito_thread, NULL);

    // Simuliamo una preparazione dati (es. caricamento file)
    printf("[Main] Sto preparando le risorse...\n");
    thrd_sleep(&(struct timespec){.tv_sec = 2}, NULL); 

    mtx_lock(&mutex);
    pronto = 1;
    printf("[Main] Risorse pronte. Segnalo il thread!\n");
    cnd_signal(&cond_var); // Sveglia il thread
    mtx_unlock(&mutex);

    thrd_join(t_id, NULL);
    
    mtx_destroy(&mutex);
    cnd_destroy(&cond_var);
    return 0;
}