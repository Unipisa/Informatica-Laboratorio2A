#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Uso: %s <input> <output>\n", argv[0]);
		return 1;
	}

	FILE *in = fopen(argv[1], "r");
	if (!in) { perror("Errore apertura input"); return 1; }

	FILE *out = fopen(argv[2], "w");
	if (!out) { perror("Errore apertura output"); fclose(in); return 1; }

	char line[1024];
	int num = 1;
	while (fgets(line, sizeof(line), in)) {
		fprintf(out, "%4d: %s", num++, line);
	}

	fclose(in);
	fclose(out);
	
	printf("Copiato %d righe in %s\n", num - 1, argv[2]);
	return 0;
}