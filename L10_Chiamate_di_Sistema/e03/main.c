#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h> // <--- fork e getpid


#define SCALL_ERROR -1
#define SCALL(r, c, e) do { if((r = c) == SCALL_ERROR) { perror(e); exit(EXIT_FAILURE); } } while(0)
#define PARENT_OR_CHILD(pid,f_parent,f_child) do { if(pid == 0) { f_child; } else { f_parent; } } while(0)


int parent(int pid){
	printf("Processo padre (PID: %d, Figlio PID: %d)\n", getpid(), pid);
	return 0;
}

int child(){
	printf("Processo figlio (PID: %d)\n", getpid());
	return 0;
}

int main() {
    pid_t pid;
	SCALL(pid, fork(), "durante fork");

	PARENT_OR_CHILD(pid,
		parent(pid),
		child()
	);

    return 0;
}

