#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SHM_NAME "/shared_memory"
#define SHM_SIZE 1024

int main() {
    // Apertura della memoria condivisa
    int fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Mappatura della memoria condivisa
    void *ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Lettura dei dati dalla memoria condivisa
    printf("Consumatore: Messaggio ricevuto: %s\n", (char *)ptr);

    // Rilascio della memoria e chiusura
    munmap(ptr, SHM_SIZE);
    close(fd);

    return 0;
}
