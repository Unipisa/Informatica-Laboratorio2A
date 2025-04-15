#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128
#define FILENAME "test.txt"

#define SCALL_ERROR -1
#define SCALL(r, c, e) do { if((r = c) == SCALL_ERROR) { perror(e); exit(EXIT_FAILURE); } } while(0)
#define SNCALL(r, c, e) do { if((r = c) == NULL) { perror(e); exit(EXIT_FAILURE); } } while(0)

#define SCALLREAD(r,loop_cond_op,read_loop_op,e) do { while((r = loop_cond_op)>0) { read_loop_op; } if(r == SCALL_ERROR) { perror(e); exit(EXIT_FAILURE); } } while(0)

int main() {

	int fd;
	SCALL(fd, open(FILENAME, O_RDONLY), "durante open");

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    
    // while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
    //     write(STDOUT_FILENO, buffer, bytesRead);   // <-- read_loop_op
    // }

    // if (bytesRead == -1) {
    //     perror("durante read");
    // }

	SCALLREAD(bytesRead, read(fd, buffer, BUFFER_SIZE), write(STDOUT_FILENO, buffer, bytesRead), "durante read");

	SCALL(fd, close(fd), "durante close");

    return 0;
}
