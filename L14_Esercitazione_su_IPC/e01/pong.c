#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#define SEM_PING "/sem_ping"
#define SEM_PONG "/sem_pong"

int main() {
    sem_t *sem_ping = sem_open(SEM_PING, 0);
    sem_t *sem_pong = sem_open(SEM_PONG, 0);

    for (int i = 0; i < 5; ++i) {
        sem_wait(sem_pong);
        printf("PONG\n");
        fflush(stdout);
        sem_post(sem_ping);
        sleep(1);
    }

    sem_close(sem_ping);
    sem_close(sem_pong);

    // cleanup solo da uno dei due processi
    sem_unlink(SEM_PING);
    sem_unlink(SEM_PONG);
    return 0;
}

