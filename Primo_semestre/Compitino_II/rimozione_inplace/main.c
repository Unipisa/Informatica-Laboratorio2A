#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int rimuovi_sottostringhe(char *str, char *subst){

	char *init_p = str, *init_sub = subst;
	int perhaps = 0, count_removal = 0;

	while (*str){
		if(*str == *subst){
			if(!perhaps){
				perhaps = 1;
				init_p = str;
			}
			str++, subst++;

			if (!*subst){
				char *source = str;
				char *dest = init_p;
				while (*source){
					*dest = *source;
					source++, dest++;
				}
				*dest = '\0';

				subst = init_sub;
				str = init_p;
				perhaps = 0;
				count_removal++;
			} 
		} else if (perhaps) {
				perhaps = 0;
				str = init_p+1;
				subst = init_sub;
			} else {
				str++;
			}
	}
	return count_removal;
}

int rimuovi_sottostringhe_alt(char *str, char *subst) {
    size_t len = strlen(subst);
    if (len == 0) return 0;
    char *read = str;
    char *write = str;
    int removed = 0;

    while (*read) {
        if (!strncmp(read, subst, len)) {
            read += len;
            removed++;
        } else {
            *write++ = *read++;
        }
    }
    *write = '\0';
    return removed;
}


int main(int argc, char *argv[]) {

	if (argc!=3){
		fprintf(stderr, "Parametri errati. Uso: %s <str_input> <subst>\n", argv[0]);
		return 1;
	}
	
	if (strlen(argv[1]) && strlen(argv[2])){
//		int num = rimuovi_sottostringhe(argv[1], argv[2]);
		int num = rimuovi_sottostringhe_alt(argv[1], argv[2]);
		if(num)
			printf("Sottostringa eliminata %d volte! Risultato: %s\n", num, argv[1]);
		else
			printf("Sottostringa non eliminata!");
	}
}