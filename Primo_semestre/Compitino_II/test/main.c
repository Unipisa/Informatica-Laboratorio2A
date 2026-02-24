#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[]) {

	if (argc!=2){
		fprintf(stderr, "Parametri errati. Uso: %s <str_input>\n", argv[0]);
		return 1;
	}

	printf("Stringa di input: %s\n", argv[1]);
	char *str = argv[1];

	while (*str){
		printf("Carattere: %c\n", *str);
		str++;
	}
	

	return 0;
}