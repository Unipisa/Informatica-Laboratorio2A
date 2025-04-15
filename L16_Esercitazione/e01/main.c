#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "macro.h"

#define BUFFER_SIZE 128
#define FILENAME "dati.txt"

int main() {
    int fd;

    // Apri il file "dati.txt" in modalità lettura
	SCALL(fd, open(FILENAME, O_RDONLY), "Errore nell'apertura del file");

	// Leggi i dati dal file e scrivili su STDOUT
	char buffer[BUFFER_SIZE];
	ssize_t bytesRead;
	SCALLREAD(bytesRead, read(fd, buffer, BUFFER_SIZE), write(STDOUT_FILENO, buffer, bytesRead), "Errore nella lettura del file");

	// Chiude il file descriptor
	SCALL(fd, close(fd), "Errore nella chiusura del file");

	return 0;
}
