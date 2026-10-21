/* Leggere due numeri interi positivi a e b. Stampare il quoziente intero e il quoziente
reale della divisione. Utilizzare un casting per ottenere il quoziente reale. Esempio:
a = 7, b = 2 -> 3 e 3.50 */


# include <stdio.h>
int main()
{
    int a, b;
    int quoziente_intero;
    float quoziente_reale;
    scanf("%d %d", &a, &b);
    quoziente_intero = a / b;
    /* Il casting modifica il tipo dell 'espressione */
    quoziente_reale = (float) a / b;
    printf("Quoziente intero: %d\n", quoziente_intero);
    printf("Quoziente reale: %.2f\n", quoziente_reale);
    return 0;
}