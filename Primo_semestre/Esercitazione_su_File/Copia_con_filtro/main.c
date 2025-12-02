#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024  // lunghezza massima di una riga

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <src> <dst>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (!src) {
        perror("Errore apertura sorgente");
        return 1;
    }

    FILE *dst = fopen(argv[2], "w");
    if (!dst) {
        perror("Errore apertura destinazione");
        fclose(src);
        return 1;
    }

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), src)) {
        // Controlla se la riga è solo "\n"
        if (strcmp(line, "\n") != 0) {
            if (fputs(line, dst) == EOF) {
                perror("Errore scrittura");
                fclose(src);
                fclose(dst);
                return 1;
            }
        }
    }

    fclose(src);
    fclose(dst);
    return 0;
}
