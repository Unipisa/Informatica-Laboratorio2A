/*  Scrivere un programma che legge due matrici quadrate di dimensione 10×10, e
fa il prodotto scalare tra le due matrici.
*/

# include <stdio.h>
#define N 10
int main()
{
    int a[N][N];
    int b[N][N];
    int prodotto = 0;
    int i, j;
    /* Leggiamo la prima matrice */
    printf("Inserisci gli elementi della prima matrice :\n");
    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) 
            scanf("%d", &a[i][j]);
    
    /* Leggiamo la seconda matrice */
    printf("Inserisci gli elementi della seconda matrice :\n");
    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) 
            scanf("%d", &b[i][j]);
        
    
    /* Calcoliamo il prodotto scalare tra le due matrici */
    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) 
            prodotto += a[i][j] * b[i][j];
        
    printf("Il prodotto scalare e ': %d\n", prodotto);
    return 0;
}