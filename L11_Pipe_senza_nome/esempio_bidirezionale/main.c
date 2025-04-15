#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int pipe1[2], pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Processo figlio
        close(pipe1[1]);  // Chiude scrittura della prima pipe
        close(pipe2[0]);  // Chiude lettura della seconda pipe

        char buffer[100];
        read(pipe1[0], buffer, sizeof(buffer));  // Riceve dal padre
        printf("Figlio ha ricevuto: %s\n", buffer);

        char response[] = "Ciao padre!";
        write(pipe2[1], response, strlen(response) + 1);  // Risponde al padre

        close(pipe1[0]);
        close(pipe2[1]);
    } else {  // Processo padre
        close(pipe1[0]);  // Chiude lettura della prima pipe
        close(pipe2[1]);  // Chiude scrittura della seconda pipe

        char msg[] = "Ciao figlio!";
        write(pipe1[1], msg, strlen(msg) + 1);  // Manda il messaggio

        char buffer[100];
        read(pipe2[0], buffer, sizeof(buffer));  // Riceve risposta
        printf("Padre ha ricevuto: %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    }

    return 0;
}
