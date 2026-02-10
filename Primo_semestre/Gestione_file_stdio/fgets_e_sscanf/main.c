#include <stdio.h>
#include <string.h>
#include <errno.h>

int load_config(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) { perror("fopen"); return 1; }

    char line[256], key[128], val[128];
    while (fgets(line, sizeof line, fp)) {
        // rimuovi newline
        line[strcspn(line, "\n")] = '\0';
        // ignora righe vuote o commenti (#)
        if (line[0] == '\0' || line[0] == '#') continue;

        if (sscanf(line, " %127[^=] = %127s ", key, val) == 2) {
            // usa key/val; qui solo demo
            printf("CFG: key='%s' val='%s'\n", key, val);
        } else {
            fprintf(stderr, "Warn: riga non valida: \"%s\"\n", line);
        }
    }

    if (ferror(fp)) { perror("fgets"); fclose(fp); return 1; }
    fclose(fp);
    return 0;
}

int main(void) { return load_config("../input.txt"); }
