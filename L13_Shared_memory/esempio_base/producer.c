#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHM_NAME "/shared_memory"
#define SHM_SIZE 1024

int main() {
    // Creazione della memoria condivisa
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    ftruncate(fd, SHM_SIZE);

    // Mappatura della memoria condivisa
    void *ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Scrittura dei dati nella memoria condivisa
    strcpy((char *)ptr, "Messaggio da produttore!");

    printf("Produttore: Messaggio scritto nella memoria condivisa\n");

    // Attendere un input prima di terminare per consentire al consumatore di leggere
    getchar();

    // Rilascio della memoria e chiusura
    munmap(ptr, SHM_SIZE);
    close(fd);
    shm_unlink(SHM_NAME);

    return 0;
}
