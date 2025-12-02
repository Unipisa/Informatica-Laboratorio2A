#include <stdio.h>
#include <string.h>
#include <errno.h>

int write_atomic_text(const char *path, const char *text) {
    char tmp[512];
    snprintf(tmp, sizeof tmp, "%s.tmp", path);

    FILE *fp = fopen(tmp, "wb");
    if (!fp) { perror("fopen tmp"); return 1; }

    size_t len = strlen(text);
    if (fwrite(text, 1, len, fp) != len || ferror(fp)) {
        perror("fwrite"); fclose(fp); remove(tmp); return 1;
    }
    if (fclose(fp) == EOF) { perror("fclose"); remove(tmp); return 1; }

    // su POSIX: rename sovrascrive atomically; altrove verificare
    if (rename(tmp, path) != 0) { perror("rename"); remove(tmp); return 1; }
    return 0;
}

int main(void) {
    return write_atomic_text("output.txt", "Hello, world!\n");
}
