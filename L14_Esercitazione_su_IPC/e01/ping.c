#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>

#define SEM_PING "/sem_ping"
#define SEM_PONG "/sem_pong"

int main() {
    sem_t *sem_ping = sem_open(SEM_PING, O_CREAT, 0600, 1);
    sem_t *sem_pong = sem_open(SEM_PONG, O_CREAT, 0600, 0);

    for (int i = 0; i < 5; ++i) {
        sem_wait(sem_ping);
        printf("PING\n");
        fflush(stdout);
        sem_post(sem_pong);
        sleep(1);
    }

    sem_close(sem_ping);
    sem_close(sem_pong);
    return 0;
}