#include <stdio.h>
#include <errno.h>

typedef struct {
    int    id;
    double value;
} record;

int save_records(const char *path, const record *a, size_t n) {
    FILE *fp = fopen(path, "wb");
    if (!fp) { perror("fopen"); return 1; }

    size_t w = fwrite(a, sizeof *a, n, fp);
    if (w != n || ferror(fp)) { perror("fwrite"); fclose(fp); return 1; }

    if (fclose(fp) == EOF) { perror("fclose"); return 1; }
    return 0;
}

int load_records(const char *path, record *a, size_t cap, size_t *n_out) {
    FILE *fp = fopen(path, "rb");
    if (!fp) { perror("fopen"); return 1; }

    size_t r = fread(a, sizeof *a, cap, fp);
    if (ferror(fp)) { perror("fread"); fclose(fp); return 1; }

    *n_out = r;
    if (fclose(fp) == EOF) { perror("fclose"); return 1; }
    return 0;
}

int main(void) {
    record out[3] = {{1, 3.14}, {2, 2.71}, {3, 1.41}}, in[3];
    size_t n = 0;
    if (save_records("data.bin", out, 3)) return 1;
    if (load_records("data.bin", in, 3, &n)) return 1;
    for (size_t i = 0; i < n; ++i) printf("%d %.2f\n", in[i].id, in[i].value);
    return 0;
}
