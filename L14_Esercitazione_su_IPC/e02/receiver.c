#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>

#define QUEUE_NAME "/chat_queue"
#define MAX_MSG_SIZE 256

int main() {
    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0600, NULL);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    char buffer[MAX_MSG_SIZE];
    while (1) {
        ssize_t bytes_read = mq_receive(mq, buffer, MAX_MSG_SIZE, NULL);
        if (bytes_read >= 0) {
            printf("Ricevuto: %s", buffer);
        } else {
            perror("mq_receive");
            break;
        }
    }

    mq_close(mq);
    mq_unlink(QUEUE_NAME);
    return 0;
}
