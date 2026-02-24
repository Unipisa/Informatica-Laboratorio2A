#include <stdio.h>
#include <threads.h>
#include <time.h>

static void sleep_ms(long ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;
    thrd_sleep(&ts, NULL);
}

int logger(void *unused) {
    
    for (int i = 0; i < 15; i++) {      
        printf("tick\n");
        sleep_ms(200);
    }
    return 0;
}

int main(void) {
    thrd_t t;
    if (thrd_create(&t, logger, NULL) != thrd_success) {
        fprintf(stderr, "thrd_create failed\n");
        return 1;
    }

    thrd_detach(t);

    printf("main exiting (process may end before logger finishes)\n");
    sleep_ms(3500); // Attenzione, le sleep non sono mai una buona soluzione per sincronizzare.
	

    return 0;
}
