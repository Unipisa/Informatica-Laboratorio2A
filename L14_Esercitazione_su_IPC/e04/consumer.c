#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>

#define SHM_NAME "/prodcons_shm"

typedef struct {
    sem_t mutex;
    sem_t full;
    sem_t empty;
    int value;
} shared_data_t;

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0600);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    shared_data_t *data = mmap(NULL, sizeof(shared_data_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    for (int i = 0; i < 10; ++i) {
        sem_wait(&data->full);
        sem_wait(&data->mutex);

        int val = data->value;
        printf("Consumer: consumato %d\n", val);
        fflush(stdout);

        sem_post(&data->mutex);
        sem_post(&data->empty);
        sleep(1);
    }

    munmap(data, sizeof(shared_data_t));
    close(shm_fd);

    // Cleanup opzionale
    // shm_unlink(SHM_NAME);

    return 0;
}
