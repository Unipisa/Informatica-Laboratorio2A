 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* mymemmove(void *dst, const void *src, size_t n) {
	char *d = (char*)dst;
	char *s = (char*)src;

	// Caso di sovrapposizione completa o nessun byte da copiare
	if (d == s || n == 0) return dst;

	// Caso di sovrapposizione parziale
	if (d < s || d >= s + n) {
		// Copia in avanti, nessun problema di sovrascrittura, infatti  se d < s
		// significa che l'area di destinazione inizia prima di quella di origine
		// e quindi non si sovrappongono, mentre se d >= s + n significa che l'area di destinazione inizia
		// dopo la fine di quella di origine, quindi non si sovrappongono.
		for (size_t i = 0; i < n; ++i) d[i] = s[i];
	} else {
		// Copia all'indietro, per evitare sovrascritture, infatti in questo caso
		// l'area di destinazione inizia all'interno di quella di origine.
		// Quindi dobbiamo copiare gli ultimi byte prima.
		for (size_t i = n; i > 0; --i) d[i-1] = s[i-1];
	}
	return dst;
}

int main(void) {
	char *msg = "abcdefg";
	size_t len = strlen(msg) + 1;
	char *buf = malloc(len);
	if (!buf){ perror("malloc"); return 1;}
	memcpy(buf, msg, len);
	printf("prima: %s\n", buf);

	// Sposta a destra 3 byte dentro lo stesso buffer
	// Risultato atteso: "abcabcdefg" troncato a len
	mymemmove(buf+3, buf, 4); // copia 'a','b','c','\0'

	printf("dopo:  %s\n", buf);
	free(buf);
	return 0;
}