/* Fissare nel programma un numero intero, ad esempio 37. Chiedere ripetutamente un
tentativo all’utente. Stampare se il tentativo è troppo grande, troppo piccolo oppure
corretto. Terminare quando il numero viene indovinato. */

# include <stdio.h>

int main()
{
    int segreto = 37; /* Numero da indovinare */
    int tentativo; /* Tentativo dell'utente */
    do {
        printf("Inserisci un tentativo: ");
        scanf("%d", &tentativo);
        if (tentativo > segreto)
            printf("Troppo grande\n");
        else 
            /* Stampo se è più piccolo di segreto o meno */
            if (tentativo < segreto)
                printf("Troppo piccolo\n");
            else
                printf("Indovinato !\n");
    } 
    while (tentativo != segreto);
    return 0;
}