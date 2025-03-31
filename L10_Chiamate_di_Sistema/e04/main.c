#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *args[] = {"/bin/ls", "-l", NULL};

    printf("Eseguendo ls -l...\n");
    
	execvp(args[0], args);
    perror("execvp");
    
	exit(EXIT_FAILURE);
}