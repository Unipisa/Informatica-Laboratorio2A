/* Leggere una sequenza di interi, che deve terminare col valore 0. Calcolare quanti
numeri sono stati inseriti, quanti sono positivi, quanti negativi e la somma dei positivi.
Il valore 0 non appartiene alla sequenza. */

#include <stdio.h>

int main() {
    int n;           /* numero letto */
    int quanti=0;    /* numero di numeri inseriti: va inizializzato a 0 perché C non lo fa */
    int positivi=0;  /* numero di numeri positivi: va inizializzato a 0 perché C non lo fa */
    int negativi=0;  /* numero di numeri negativi: va inizializzato a 0 perché C non lo fa */

    do{
        /* Leggi un numero */
        scanf("%d\n", &n);
        /* Controlla se il numero è 0 */
        if(n==0) 
            /* Se il numero è 0, esce dal ciclo: occorre OBBLIGATOIAMENTE break per uscire dal ciclo più interno */
            break;
        ++quanti;
        /* Conta i numeri positivi e negativi */
        if ( n>0) 
            ++positivi;
        else 
            ++negativi;
    } while (n!=0);
    /* Stampa i risultati */
    printf("Quanti: %d\n", quanti);
    printf("Positivi: %d\n", positivi);
    printf("Negativi: %d\n", negativi);
}