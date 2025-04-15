#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "macro.h"

#define BUFFER_SIZE 1024

int pipefd[2];

void child() {

	// Codice del processo figlio
	int ret;

	// Chiudi il lato di lettura della pipe
	SCALL(ret, close(pipefd[0]), "Errore nella chiusura del lato di lettura della pipe");

	// Scrivi un messaggio nella pipe
	SCALL(ret, write(pipefd[1], "Messaggio dal processo figlio\n", strlen("Messaggio dal processo figlio\n")), "Errore nella scrittura nella pipe");

	// Chiudi il lato di scrittura della pipe
	SCALL(ret, close(pipefd[1]), "nella chiusura del lato di scrittura della pipe"); // Chiudi il lato di scrittura della pipe
}

void parent(pid_t pid) {
	// Codice del processo padre
	int ret;
	char buffer[BUFFER_SIZE];

	// Chiudi il lato di scrittura della pipe
	SCALL(ret, close(pipefd[1]), "Errore nella chiusura del lato di scrittura della pipe");

	// Leggi il messaggio dalla pipe
	SCALL(ret, read(pipefd[0], buffer, sizeof(buffer)), "Errore nella lettura dalla pipe");

	// Stampa il messaggio ricevuto
	printf("Messaggio letto dal processo padre: %s", buffer);

	// chiudi il lato di lettura della pipe
	SCALL(ret, close(pipefd[0]), "Errore nella chiusura del lato di lettura della pipe"); // Chiudi il lato di lettura della pipe
}



int main() {

    pid_t pid;
	int ret;

	// Crea una pipe senza nome
	SCALL(ret, pipe(pipefd), "Errore nella creazione della pipe");

    // Crea un nuovo processo figlio
	SCALL(pid, fork(), "Errore nella creazione del processo figlio");

	// Esegui il codice del processo padre o del processo figlio
	PARENT_OR_CHILD(pid, parent, child);

    return 0;
}
