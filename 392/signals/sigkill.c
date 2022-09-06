/*** sigkill.c ***/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void sig_handler(int sig) {
    printf("\nOuch!\n");
    sleep(1);
    fflush(stdout);
    printf("Stop it!\n");
}

int main() {
    /* Installing signal handler */
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");

    for (size_t i = 0; ; i++) {
        printf("%d\n", i);
        sleep(1);
        if (i%5 == 0) {
            kill(getpid(), SIGINT);
        }
    }
    return 0;
}
