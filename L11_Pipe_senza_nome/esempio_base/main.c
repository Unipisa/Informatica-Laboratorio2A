#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int fd[2];  // file descriptor per la pipe: fd[0] lettura, fd[1] scrittura
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Processo figlio
        close(fd[1]);  // Chiude il lato scrittura della pipe
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("Figlio ha letto: %s\n", buffer);
        close(fd[0]);
    } else {  // Processo padre
        close(fd[0]);  // Chiude il lato lettura della pipe
        char msg[] = "Messaggio dal padre";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    }

    return 0;
}
