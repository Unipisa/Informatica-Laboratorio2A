#include <stdio.h>
#include <stdlib.h>
#define MAX_BUF 1024

int scrivi_righe_multiplo(FILE* F, int A, FILE* F_out){

	char buf[1024];
	int line_count = 0;

	if (!F || !F_out || A <= 0){
		if (!F) fprintf(stderr, "Errore nell'accesso al file di input.");
		else if (!F_out) fprintf (stderr, "Errore nell'accesso al file di output.");
				else fprintf (stderr, "Errore: il valore di A deve essere maggiore di 0.\n");
		return -1;
	}

	while (fgets(buf, MAX_BUF, F))
		if (line_count++ % A == 0)
			fputs(buf, F_out);

	if(fclose(F) || fclose(F_out)){
		perror("Errore chiusura file.");
		return -1;
	}

	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 4){
		fprintf(stderr, "Uso: %s <file_input> <A> <file_output>\n", argv[0]);
		return 1;
	}

	FILE* F_in = fopen(argv[1], "r");
	if (!F_in){
		perror("Errore apertura file di input");
		return 1;
	}

	int A = atoi(argv[2]);
	FILE* F_out = fopen(argv[3], "w");
	if (!F_out){
		perror("Errore apertura file di output");
		fclose(F_in);
		return 1;
	}

	return scrivi_righe_multiplo(F_in, A, F_out) != 0;
}