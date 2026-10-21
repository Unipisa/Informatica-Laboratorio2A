
/* Scrivere un programma di gestione dell’anagrafe dei dipendenti di un’azienda.
    • Per ogni dipendente leggere: codice identificativo, età, stipendio e ruolo.
    • Il ruolo va rappresentato con una enum: 0 - dirigente, 1 - quadro, 2 - operaio, 3 -
        impiegato.
    • Stampare codice, età e ruolo dei dipendenti che guadagnano meno dello
        stipendio medio.
    Il numero di dipendenti da inserire è fissato ad N. Per ogni dipendente, si chieda in
    input il codice identificativo, controllando se è diverso da uno già immesso e
    richiedendolo se è diverso, poi l’età, lo stipendio e infine il tipo di dipendente
    Esempio di output
        3 22 operaio
        4 32 impiegato */

# include <stdio.h>
# include <stdlib.h>
#define N 10
/* Definizione del tipo enum per il ruolo */
typedef enum {dirigente, quadro, operaio, impiegato} ruolo_t;
/* Definizione del tipo struttura per il dipendente */
typedef struct {
    int id;
    int eta;
    float salario;
    ruolo_t ruolo;
} dipendente_t;


int main(int argc , char *argv []) {
    int i, id_dip , eta_dip , ruolo_dip , eta;
    float media = 0, salario_dip;
    dipendente_t dipendenti[N];
    scanf("%d", &eta);
    for (i = 0; i < N; i++) {
        printf("Inserire id, eta, salario e ruolo del dipendente %d: ", i+1);
        scanf("%d", &id_dip);
        scanf("%d", &eta_dip);
        scanf("%f", &salario_dip);
        scanf("%d", &ruolo_dip);
        dipendenti[i].id = id_dip;
        dipendenti[i].eta = eta_dip;
        dipendenti[i]. salario = salario_dip;
        dipendenti[i]. ruolo = ruolo_dip;
        media += salario_dip;
    }
    media /= N;
    /* Stampa dei dipendenti che guadagnano meno dello stipendio medio */
    for (i = 0; i < N; i++)
        if (dipendenti[i]. salario < media && dipendenti[i].eta <= eta) {
            printf("%d ", dipendenti[i].id);
            printf("%d ", dipendenti[i].eta);
            /* Stampa del ruolo */
            switch (dipendenti[i]. ruolo) {
                case dirigente:
                    printf("dirigente\n");
                    break;
                case quadro:
                    printf("quadro\n");
                    break;
                case operaio:
                    printf("operaio\n");
                    break;
                default:
                    printf("impiegato\n");
            }
        }
    return 0;
}        