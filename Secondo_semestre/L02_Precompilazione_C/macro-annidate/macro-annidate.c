#include <stdio.h>

#define QUADRATO(x) ((x) * (x))
#define DOPPIO_QUADRATO(x) (2 * QUADRATO(x))

int main(){
	int x = 3;
	printf("Il quadrato di %d è %d\n", x, QUADRATO(x));
	printf("Il doppio del quadrato di %d è %d\n", x, DOPPIO_QUADRATO(x));
	return 0;
}