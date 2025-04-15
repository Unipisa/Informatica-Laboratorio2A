#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>

#define QUEUE_NAME "/chat_queue"
#define MAX_MSG_SIZE 256

int main() {

	struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

	// Creazione della coda di messaggi
    //mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0600, NULL);
	mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY | O_EXCL, 0600, &attr);
    if (mq == -1) {
        perror("mq_open");
        exit(1);
    }

    char buffer[MAX_MSG_SIZE];
    printf("Scrivi messaggi (CTRL+D per terminare):\n");
    while (fgets(buffer, MAX_MSG_SIZE, stdin) != NULL) {
        mq_send(mq, buffer, strlen(buffer) + 1, 0);
    }

    mq_close(mq);
    return 0;
}
