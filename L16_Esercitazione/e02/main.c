#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h> // fork e getpid

#include "macro.h"

void parent (pid_t pid) {
	printf("Il processo padre è in esecuzione.\n");
	// Attendi la terminazione del processo figlio
	int status;
	int ret;
	SCALL(ret, waitpid(pid, &status, 0), "nella waitpid");
	printf("Il processo padre ha terminato l'attesa.\n");
}

void child () {
	printf("Il processo figlio è in esecuzione.\n");
	// Esegui un nuovo programma (esempio: ls)
	char *args[] = {"/bin/ls", NULL};
	execv(args[0], args);
	perror("execv fallita");
}


int main() {
    pid_t pid;

    // Crea un nuovo processo figlio
	SCALL(pid, fork(), "nella fork");

	// Esegui il codice del processo padre o del processo figlio
	PARENT_OR_CHILD(pid, parent, child);

    return 0;
}
