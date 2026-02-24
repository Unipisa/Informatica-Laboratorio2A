#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nomefile>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Errore apertura file");
        return 1;
    }

    long bytes = 0;
    long lines = 0;
    long words = 0;
    int in_word = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF) {
        bytes++;

        if (ch == '\n') {
            lines++;
        }

        if (isspace(ch)) {
            in_word = 0;
        } else {
            if (!in_word) {
                words++;
                in_word = 1;
            }
        }
    }

    fclose(fp);

    printf("Linee: %ld\n", lines);
    printf("Parole: %ld\n", words);
    printf("Byte: %ld\n", bytes);

    return 0;
}
