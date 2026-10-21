/* Scrivere un programma che inverta gli elementi di un array di interi A, di
dimensione 10. Il programma deve invertire l’array senza utilizzare un array di
appoggio, ossia scambiare il contenuto della prima e dell’ultima cella, della
seconda e della penultima, ecc… ed infine stampare a video ogni singolo
elemento dell’array modificato. */

# include <stdio.h>
int main() {
    int i, j, scambio;
    int A[10];
    for (i = 0; i < 10; i++)
        A[i] = i;
    /* Inversione : scorro l'array fino alla meta ' */
    for (i = 0; i < 10 / 2; i++) {
        j = (10 - 1) - i;
        scambio = A[i];
        A[i] = A[j];
        A[j] = scambio;
    }
    for (i = 0; i < 10; i++)
        printf("%d\n", A[i]);
    return 0;
}