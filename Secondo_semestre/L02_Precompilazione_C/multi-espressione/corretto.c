#include <stdio.h>
#include <stdlib.h>

#define CHECK_AGE(anni) ( \
    printf("Quanti anni hai: "), \
    scanf("%d", &anni), \
    (anni < 18 ? (printf("Sei minorenne\n"), exit(1), 0) : 0) \
)

int main () {
	int anni;
	do
		CHECK_AGE(anni);
	while (anni < 18);
}