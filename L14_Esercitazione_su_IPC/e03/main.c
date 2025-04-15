#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define SHM_NAME "/shared_counter"
#define NUM_ITERATIONS 10

typedef struct {
    sem_t mutex;
    int counter;
} shared_data_t;

int main() {
    int shm_fd;
    shared_data_t *data;
    int first_time = 0;

    // Tenta di aprire o creare la shared memory
    shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_EXCL, 0600);
    if (shm_fd == -1) {
        if (errno == EEXIST) {
            shm_fd = shm_open(SHM_NAME, O_RDWR, 0600);
        } else {
            perror("shm_open");
            exit(1);
        }
    } else {
        // Se l'ha appena creata, bisogna inizializzarla
        ftruncate(shm_fd, sizeof(shared_data_t));
        first_time = 1;
    }

    // Mappatura della shared memory
    data = mmap(NULL, sizeof(shared_data_t), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Inizializza il semaforo solo una volta
    if (first_time) {
        sem_init(&data->mutex, 1, 1); // pshared=1 perché condiviso tra processi
        data->counter = 0;
    }

    // Incrementa il contatore NUM_ITERATIONS volte
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        sem_wait(&data->mutex);
        int val = data->counter;
        printf("PID %d legge %d, lo incrementa a %d\n", getpid(), val, val + 1);
        data->counter = val + 1;
        sem_post(&data->mutex);
        sleep(1); // pausa per rendere visibile la concorrenza
    }

    munmap(data, sizeof(shared_data_t));
    close(shm_fd);

    return 0;
}
