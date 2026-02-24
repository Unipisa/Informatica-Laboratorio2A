#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 4096  

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <src> <dst>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        perror("Errore apertura sorgente");
        return 1;
    }

    FILE *dst = fopen(argv[2], "wb");
    if (!dst) {
        perror("Errore apertura destinazione");
        fclose(src);
        return 1;
    }

    char buffer[BLOCK_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BLOCK_SIZE, src)) > 0) {
        if (fwrite(buffer, 1, bytesRead, dst) != bytesRead) {
            perror("Errore scrittura");
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    fclose(src);
    fclose(dst);
    return 0;
}
