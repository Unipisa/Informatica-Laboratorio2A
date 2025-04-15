#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

#define QUEUE_NAME "/test_queue"
#define MAX_SIZE 1024
#define MSG_STOP "exit"

int main() {
    mqd_t mq;
    char buffer[MAX_SIZE];
    struct mq_attr attr;

    // Definire gli attributi della coda
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    // Creare o aprire la message queue
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    pid_t pid = fork(); // Creare un processo figlio

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        // Processo genitore (Produttore)
        int nbytes;

        // Inviare messaggi
        while (1) {
            printf("Inserisci un messaggio (o 'exit' per terminare): \n");
			fflush(stdout); // Assicurarsi che il prompt venga stampato immediatamente
            
            // Usare read per ottenere l'input dall'utente
            nbytes = read(STDIN_FILENO, buffer, MAX_SIZE);
            if (nbytes == -1) {
                perror("read");
                exit(1);
            }

            // Aggiungere il carattere di fine stringa
            if (nbytes > 0 && buffer[nbytes - 1] == '\n') {
                buffer[nbytes - 1] = '\0';
            }

            // Se il messaggio è "exit", inviare comunque il messaggio "exit" e terminare
            if (strcmp(buffer, MSG_STOP) == 0) {
                mq_send(mq, buffer, strlen(buffer) + 1, 0);  // Invia il messaggio "exit"
                break;
            }

            // Inviare il messaggio alla coda
            if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
                perror("mq_send");
                exit(1);
            }
        }

        // Chiudere la coda
        if (mq_close(mq) == -1) {
            perror("mq_close");
            exit(1);
        }

        // Attendere che il processo figlio termini
        wait(NULL);

        // Rimuovere la coda
        if (mq_unlink(QUEUE_NAME) == -1) {
            perror("mq_unlink");
            exit(1);
        }

    } else {
        // Processo figlio (Consumatore)

        // Ricevere messaggi
        while (1) {
            ssize_t bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);
            if (bytes_read == -1) {
                perror("mq_receive");
                exit(1);
            }

            printf("Ricevuto messaggio: %s\n", buffer);

            // Se il messaggio è "exit", terminare
            if (strcmp(buffer, MSG_STOP) == 0) {
                break;
            }
        }

        // Chiudere la coda
        if (mq_close(mq) == -1) {
            perror("mq_close");
            exit(1);
        }
    }

    return 0;
}
