#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>
#include <errno.h>

#define SHM_NAME "/prodcons_shm"

typedef struct {
    sem_t mutex;
    sem_t full;
    sem_t empty;
    int value;
} shared_data_t;

int main() {
    int shm_fd;
    shared_data_t *data;
    int first_time = 0;

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (shm_fd == -1) {
        if (errno == EEXIST) {
            shm_fd = shm_open(SHM_NAME, O_RDWR, 0600);
        } else {
            perror("shm_open");
            exit(1);
        }
    } else {
        ftruncate(shm_fd, sizeof(shared_data_t));
        first_time = 1;
    }

    data = mmap(NULL, sizeof(shared_data_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    if (first_time) {
        sem_init(&data->mutex, 1, 1);
        sem_init(&data->empty, 1, 1);
        sem_init(&data->full, 1, 0);
    }

    for (int i = 0; i < 10; ++i) {
        sem_wait(&data->empty);
        sem_wait(&data->mutex);

        data->value = i;
        printf("Producer: prodotto %d\n", i);
        fflush(stdout);

        sem_post(&data->mutex);
        sem_post(&data->full);
        sleep(1);
    }

    munmap(data, sizeof(shared_data_t));
    close(shm_fd);
    return 0;
}
