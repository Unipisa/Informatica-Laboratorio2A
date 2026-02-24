#include <stdio.h>
#include <stdlib.h>


#define CHECK_AGE(anni) \
do { \
    printf("Quanti anni hai: "); \
    scanf("%d", &anni); \
    if(anni < 18) { printf("Sei minorenne\n");} else {return 1;} \
} while(0)

int main () {
	int anni;
	do
		CHECK_AGE(anni);
	while (anni < 18);
}