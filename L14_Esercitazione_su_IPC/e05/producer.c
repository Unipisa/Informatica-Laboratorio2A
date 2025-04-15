#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define QUEUE_NAME "/log_queue"
#define MAX_MSG_SIZE 256

int main() {

	struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;


    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0600, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    char message[MAX_MSG_SIZE];
    for (int i = 0; i < 5; ++i) {
        snprintf(message, MAX_MSG_SIZE, "Messaggio dal produttore %d", i);
        mq_send(mq, message, strlen(message) + 1, 0);
        printf("Produttore %d: inviato '%s'\n", i, message);
        sleep(1);
    }

    mq_close(mq);
    return 0;
}
