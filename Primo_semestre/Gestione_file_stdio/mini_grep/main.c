#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    if (argc != 2) { fprintf(stderr, "Uso: %s <substr>\n", argv[0]); return 2; }
    const char *needle = argv[1];

    char line[1024];
    while (fgets(line, sizeof line, stdin)) {
        if (strstr(line, needle)) fputs(line, stdout);
    }
    if (ferror(stdin)) { perror("fgets"); return 1; }
    return 0;
}
