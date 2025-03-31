#include <stdio.h>
#include <threads.h>

thread_local char *identita;

void smaschera(void *arg) {
	identita = arg;
}

char* rivela_identita() {
	return identita;
}

int scopri_identita(void *arg) {
	smaschera(arg);
    printf("Sono %s! Ma shhh, non dirlo a nessuno!\n", rivela_identita());
    return thrd_success;
}

int main() {
    thrd_t t1, t2;
    
    thrd_create(&t1, scopri_identita, "Spider-Man");
    thrd_create(&t2, scopri_identita, "Batman");

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);

    return 0;
}
