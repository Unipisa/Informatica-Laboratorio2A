#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Processo figlio esegue `ls`
        close(fd[0]);  // Chiude lato lettura
        dup2(fd[1], STDOUT_FILENO);  // Collega stdout alla pipe
        close(fd[1]);  
        execlp("ls", "ls", NULL);
        perror("execlp ls");  // Se execlp fallisce
        exit(EXIT_FAILURE);
    } else {  // Processo padre esegue `wc -l`
        close(fd[1]);  // Chiude lato scrittura
        dup2(fd[0], STDIN_FILENO);  // Collega stdin alla pipe
        close(fd[0]);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    return 0;
}
