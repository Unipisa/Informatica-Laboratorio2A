#define _POSIX_C_SOURCE 200809L // Enable POSIX features for sigaction


#include <stdio.h>
#include <stdlib.h> // Per exit()
#include <signal.h> // Per sigaction, struct sigaction, SIGINT
#include <sys/types.h> // Per tipi di dati aggiuntivi, se necessario
#include <unistd.h> // Per pause(), write()
#include <string.h> // Per strlen()

// --- Gestore di Segnali (Signal Handler) ---
// Questa funzione verrà eseguita quando il processo riceve SIGINT.
// NOTA IMPORTANTE SULLA SICUREZZA:
// Idealmente, dovremmo usare solo funzioni async-signal-safe qui.
// printf NON è tecnicamente sicuro, ma lo usiamo per semplicità
// in questo esempio introduttivo. Un'alternativa più sicura
// con write() è mostrata commentata sotto.
void handle_sigint(int sig) {
    // Versione *non* sicura ma più semplice da leggere:
    printf("\nRicevuto segnale SIGINT (%d)! Continuo l'esecuzione.\n", sig);
    printf("Premi Ctrl+C di nuovo per provare ancora.\n");
    fflush(stdout); // Forziamo l'output, dato che printf bufferizza

    /*
    // Versione async-signal-safe con write():
    const char *msg = "\nRicevuto segnale SIGINT! Continuo.\n";
    // write è sicura: (file descriptor 1 = stdout, messaggio, lunghezza)
    write(STDOUT_FILENO, msg, strlen(msg));
    */
}

int main() {
    struct sigaction sa;

    printf("Programma avviato (PID: %d). Premi Ctrl+C.\n", getpid());

    // 1. Configura la struttura sigaction
    // È buona norma inizializzarla a zero per evitare valori spazzatura
    memset(&sa, 0, sizeof(sa));

    // 2. Imposta il gestore del segnale
    // Usiamo sa_handler perché non useremo SA_SIGINFO
    sa.sa_handler = handle_sigint;

    // 3. Imposta la maschera dei segnali da bloccare durante l'esecuzione del gestore
    // sigemptyset inizializza sa_mask a un set vuoto, così nessun segnale
    // aggiuntivo viene bloccato (oltre a SIGINT stesso, che è bloccato di default)
    sigemptyset(&sa.sa_mask);

    // 4. Imposta i flag (opzionale)
    // Mettiamo 0 per ora (nessun flag speciale)
    // SA_RESTART sarebbe utile se avessimo chiamate bloccanti nel loop principale
    sa.sa_flags = 0;
    // sa.sa_flags = SA_RESTART; // Prova a decommentare se usi read() nel loop

    // 5. Registra il gestore per il segnale SIGINT
    // Passiamo l'indirizzo della nostra struttura 'sa'.
    // Il terzo argomento è NULL perché non ci interessa salvare la vecchia azione.
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Errore in sigaction"); // Stampa un messaggio di errore descrittivo
        exit(EXIT_FAILURE);
    }

    printf("Gestore per SIGINT installato. In attesa di segnali...\n");

    // 6. Loop principale - Aspetta indefinitamente
    // La funzione pause() sospende l'esecuzione del processo
    // finché non viene consegnato un segnale il cui gestore
    // esegue un 'return'.
    while (1) {
        //printf("In attesa...\n"); // Puoi aggiungere stampe qui se vuoi
        pause(); // Aspetta l'arrivo di un segnale
        // L'esecuzione riprende qui *dopo* che il gestore di segnali ha terminato
        printf("...pause() è ritornata dopo la gestione del segnale.\n");
    }

    // Questa parte non verrà mai raggiunta nel nostro caso
    printf("Programma terminato.\n");
    return 0; // Equivalente a exit(EXIT_SUCCESS);
}