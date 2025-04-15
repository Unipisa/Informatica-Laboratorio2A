#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define QUEUE_NAME "/log_queue"
#define MAX_MSG_SIZE 256

int main() {
    mqd_t mq = mq_open(QUEUE_NAME, O_RDONLY | O_CREAT, 0600, NULL);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    char message[MAX_MSG_SIZE];
    ssize_t bytes_read;

    while (1) {
        bytes_read = mq_receive(mq, message, MAX_MSG_SIZE, NULL);
        if (bytes_read >= 0) {
            printf("Logger: ricevuto '%s'\n", message);
        } else {
            perror("mq_receive");
            break;
        }
    }

    mq_close(mq);
    mq_unlink(QUEUE_NAME);
    return 0;
}
