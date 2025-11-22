#include <stdio.h>
#include <errno.h>

long file_size(const char *path) {
    long size = -1;
    FILE *fp = fopen(path, "rb");
    if (!fp) { perror("fopen"); return -1; }

    if (fseek(fp, 0, SEEK_END) == 0) {
        size = ftell(fp);            // long: attenzione a file >2GB su LP32
    } else {
        perror("fseek");
    }
    if (fclose(fp) == EOF) perror("fclose");
    return size;
}

int main(void) {
    long sz = file_size("data.bin");
    if (sz >= 0) printf("Size = %ld bytes\n", sz);
    return (sz < 0);
}
