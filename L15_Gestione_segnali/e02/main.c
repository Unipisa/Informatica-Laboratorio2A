#define _POSIX_C_SOURCE 200809L // Enable POSIX features for sigaction

#include <stdio.h>
#include <stdlib.h>     // Per exit(), EXIT_FAILURE, EXIT_SUCCESS
#include <signal.h>     // Per sigaction, sigemptyset, ecc.
#include <unistd.h>     // Per write(), sleep(), getpid()
#include <string.h>     // Per memset(), strlen()
#include <time.h>       // Per time(), ctime()
#include <errno.h>      // Per perror()

// --- Variabili Globali ---

// Flag per indicare al loop principale di terminare.
// 'volatile': dice al compilatore che il suo valore può cambiare inaspettatamente
//             (a causa del gestore di segnali), quindi non deve ottimizzare
//             assumendo che rimanga costante.
// 'sig_atomic_t': tipo intero che garantisce letture/scritture atomiche
//                 anche in presenza di segnali (evita race condition).
volatile sig_atomic_t g_terminate_request = 0;

// Puntatore al file che terremo aperto. Globale per semplicità in questo esempio.
FILE *g_logfile = NULL;
const char *g_logfilename = "program_activity.log";

// --- Gestore del Segnale SIGINT ---
// Questa funzione viene chiamata quando il processo riceve SIGINT (Ctrl+C).
// Deve essere estremamente semplice e usare solo funzioni async-signal-safe.
void sigint_handler(int signal_number) {
    // 1. Imposta il flag per comunicare al main loop di terminare.
    g_terminate_request = 1;

    // 2. Scrivi un messaggio *semplice* sulla console usando write()
    //    (che è async-signal-safe, a differenza di printf).
    const char msg[] = "\nCtrl+C premuto! Avvio procedura di terminazione...\n";
    // Ignoriamo eventuali errori di write qui per semplicità del gestore
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);

    // !!! COSE DA NON FARE ASSOLUTAMENTE QUI DENTRO: !!!
    // - Chiamare printf(), fprintf(), sprintf(), ecc.
    // - Chiamare fclose(), fopen(), malloc(), free(), ecc.
    // - Chiamare exit() (è meglio lasciare che il main loop gestisca la terminazione)
}

// --- Funzione di Cleanup ---
// Chiamata dal main *dopo* che il flag di terminazione è stato rilevato.
// Qui possiamo usare funzioni non async-signal-safe perché siamo nel flusso normale.
void cleanup_and_exit() {
    printf("Esecuzione cleanup prima della terminazione.\n");

    if (g_logfile != NULL) {
        printf("Chiusura del file di log: %s\n", g_logfilename);
        // Scriviamo un ultimo messaggio nel file prima di chiuderlo
        fprintf(g_logfile, "[%ld] Chiusura log a seguito di SIGINT.\n", (long)time(NULL));

        if (fclose(g_logfile) != 0) {
            perror("Attenzione: errore durante la chiusura del file di log");
            // Non usciamo subito, ma segnaliamo il problema
        }
        g_logfile = NULL; // Buona pratica: azzera il puntatore dopo la chiusura
    } else {
        printf("Nessun file di log da chiudere.\n");
    }

    printf("Cleanup completato. Uscita.\n");
    exit(EXIT_SUCCESS); // Termina il programma con successo
}

// --- Main ---
int main() {
    struct sigaction sa_sigint;
    time_t current_time;
    int loop_counter = 0;

    printf("Programma avviato (PID: %d).\n", getpid());
    printf("Verranno scritti messaggi nel file '%s'.\n", g_logfilename);
    printf("Premi Ctrl+C per terminare il programma in modo pulito.\n");

    // --- Apertura del file di log ---
    g_logfile = fopen(g_logfilename, "a"); // Apre in modalità 'append'
    if (g_logfile == NULL) {
        perror("ERRORE: Impossibile aprire il file di log");
        exit(EXIT_FAILURE);
    }
    current_time = time(NULL);
    fprintf(g_logfile, "--- Log Sessione Iniziata [%ld] ---\n", (long)current_time);
    fflush(g_logfile); // Assicura che l'intestazione sia scritta subito

    // --- Configurazione del gestore per SIGINT ---
    memset(&sa_sigint, 0, sizeof(sa_sigint)); // Azzera la struttura
    sa_sigint.sa_handler = sigint_handler;    // Imposta la nostra funzione gestore
    sigemptyset(&sa_sigint.sa_mask);          // Non bloccare altri segnali durante l'esecuzione del gestore
    sa_sigint.sa_flags = SA_RESTART;          // Riavvia chiamate di sistema lente (come sleep) se interrotte

    // Registra il gestore
    if (sigaction(SIGINT, &sa_sigint, NULL) == -1) {
        perror("ERRORE: sigaction fallita");
        // Proviamo comunque a chiudere il file prima di uscire
        if (g_logfile) {
            fclose(g_logfile);
        }
        exit(EXIT_FAILURE);
    }

    printf("Gestore SIGINT installato. Inizio ciclo principale...\n");

    // --- Loop Principale ---
    // Continua finché il gestore di SIGINT non imposta g_terminate_request a 1
    while (g_terminate_request == 0) {
        // Simula del lavoro: scrive data e ora nel file di log
        current_time = time(NULL);
        fprintf(g_logfile, "[%ld] Loop %d - Tutto ok. %s", (long)current_time, loop_counter++, ctime(&current_time));
        fflush(g_logfile); // Forza la scrittura nel file

        printf("Ciclo %d completato. In attesa... (Premi Ctrl+C per uscire)\n", loop_counter -1);

        // Aspetta per un po'. Se arriva SIGINT durante sleep,
        // il gestore viene eseguito, imposta g_terminate_request,
        // e al ritorno dal gestore, sleep termina (o viene riavviata
        // brevemente a seconda di SA_RESTART e del sistema).
        // Il controllo 'while' successivo rileverà il flag.
        sleep(5); // Aspetta 5 secondi
    }

    // --- Uscita dal Loop ---
    // Il codice arriva qui *solo* dopo che il gestore di SIGINT
    // è stato eseguito e ha impostato g_terminate_request = 1.

    printf("Flag di terminazione rilevato.\n");

    // --- Esegui Cleanup ---
    // Ora è sicuro chiamare funzioni come fclose, printf, ecc.
    cleanup_and_exit();

    // Questa riga non dovrebbe essere mai raggiunta perché cleanup_and_exit() chiama exit()
    return 0;
}