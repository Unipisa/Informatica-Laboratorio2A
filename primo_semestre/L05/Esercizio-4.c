/* Scrivere un programma che chieda all’utente quanti valori vuole inserire. Leggere i
valori come numeri in virgola mobile (float). Si assuma che i valori inseriti
rappresentino numeri interi (ad esempio 4.0, 7.0, 12.0). Per ogni valore, stabilire se
il corrispondente numero intero è pari o dispari. Al termine, stampare quanti valori
pari e quanti valori dispari sono stati inseriti. */

# include <stdio.h>
int main()
{
    int n; /* Numero di valori da inserire */
    int i; /* Indice del ciclo */
    int valore_intero; /* Valore intero convertito */
    int pari = 0; /* Contatore dei valori pari */
    int dispari = 0; /* Contatore dei valori dispari */
    float valore;
    printf("Quanti valori vuoi inserire? ");
    scanf("%d", &n);
    /* Inseriamo i valori */
    for (i = 0; i < n; i++) {
        printf("Inserisci un valore: ");
        scanf("%f", &valore);
        /* Convertiamo il valore da float a int */
        valore_intero = (int) valore;
        /* Il modulo si applica al valore intero */
        if (valore_intero % 2 == 0) {
            printf("Pari\n");
            pari ++;
        } 
        else {
            printf("Dispari\n");
            dispari ++; 
        }
    }
    printf("Valori pari: %d\n", pari);
    printf("Valori dispari: %d\n",dispari);
    return 0;
}