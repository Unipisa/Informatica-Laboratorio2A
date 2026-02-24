 #include <stdio.h>
#include <ctype.h>

void normalize(char *s) {
	// Rimuovi spazi iniziali
	char *p = s; 
	while (*p && isspace((unsigned char)*p)) p++;

	// Copia il resto della stringa normalizzando
	char *w = s; int in_sp = 0;

	// Scorri fino alla fine della stringa
	for (; *p; ++p) {

		char c = (char)*p;
		// Gestisci spazi e caratteri
		if (isspace(c)) { 
			in_sp = 1; 
		} else {
			
			if (in_sp && w != s) *w++=' ';

			// Aggiungi carattere minuscolo
			*w++ = (char)tolower(c);
			in_sp = 0;
		}
	}

	// Rimuovi eventuale spazio finale
	if (w > s && *(w-1) == ' ') --w;
	*w = '\0';
}

int main(void) {
	char buf[256];
	if (!fgets(buf, sizeof(buf), stdin)) return 0;
	// rimuovi eventuale '\n' finale
	char *nl = buf; while (*nl) { if (*nl=='\n'){*nl='\0';break;} nl++; }
	printf("prima:  '%s'\n", buf);
	normalize(buf);
	printf("dopo:   '%s'\n", buf);
	return 0;
}