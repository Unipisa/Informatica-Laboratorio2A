#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SCALL_ERROR -1
#define SCALL(r, c, e) do { if((r = c) == SCALL_ERROR) { perror(e); exit(EXIT_FAILURE); } } while(0)
#define PARENT_OR_CHILD(pid,f_parent,f_child) do { if(pid == 0) { f_child; } else { f_parent; } } while(0)

int parent (int pid){
	// Processo padre
	int status;
	pid_t child_pid;

	// Attendiamo il figlio
	SCALL(child_pid, waitpid(pid, &status, 0), "durante waitpid");

	// Stampiamo lo stato di uscita del figlio
	if (WIFEXITED(status)) {
		printf("Figlio (PID: %d) uscito con status %d\n", child_pid, WEXITSTATUS(status));
	}

	return 0;
}

int child(){
	// Processo figlio: esegue "ls -l"
	printf("Processo figlio (PID: %d) eseguendo ls -l...\n", getpid());
	execlp("ls", "ls", "-l", NULL);
	
	// Se exec fallisce, stampiamo un errore ed usciamo
	perror("durante execlp");
	exit(EXIT_FAILURE);
}

int main() {

    pid_t pid;

	// Creiamo un processo figlio
	SCALL(pid, fork(), "durante fork");

	// Chiamiamo la macro PARENT_OR_CHILD per eseguire il codice corretto
	PARENT_OR_CHILD(pid,
		parent(pid),
		child()
	);

    return 0;
}
