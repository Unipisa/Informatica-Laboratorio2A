#include <stdio.h>
#include <stdlib.h>

#define CHECK_AGE(anni) { \
    printf("Quanti anni hai: "); \
    scanf("%d", &anni);	\
    if(anni < 18) {printf("Età insufficiente\n"); return 1;} else {return 0;} \
}


int main () {
	int anni;
	do
		CHECK_AGE(anni);
	while (anni < 18);
}