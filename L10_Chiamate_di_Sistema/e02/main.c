#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#define FILENAME "test.txt"
#define CURRENT_DIR "."

#define SCALL_ERROR -1
#define SCALL(r, c, e) do { if((r = c) == SCALL_ERROR) { perror(e); exit(EXIT_FAILURE); } } while(0)
#define SNCALL(r, c, e) do { if((r = c) == NULL) { perror(e); exit(EXIT_FAILURE); } } while(0)

#define SNCALLREAD(r,loop_cond_op,read_loop_op,e) do { while((r = loop_cond_op) != NULL) { read_loop_op; } if(errno == SCALL_ERROR) { perror(e); exit(EXIT_FAILURE); } } while(0)


int main() {
	int result;
    struct stat fileStat;
	SCALL(result, stat(FILENAME, &fileStat), "durante stat");

    printf("Dimensione File: %ld bytes\n", fileStat.st_size);

	DIR *dir;
	SNCALL(dir, opendir(CURRENT_DIR), "durante opendir");

    struct dirent *entry;
    // while ((entry = readdir(dir)) != NULL) {
    //     printf("Found: %s\n", entry->d_name);
    // }

	SNCALLREAD(entry, readdir(dir), printf("Trovato: %s\n", entry->d_name), "durante readdir");

	SCALL(result, closedir(dir), "durante closedir");
	return 0;
}
