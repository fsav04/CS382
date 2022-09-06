/*** sig3.c ***/
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

    /* declare a struct sigaction */
    struct sigaction action;
    /* set the handler */
    action.sa_handler = sig_handler;
    /* Install the signal handler */
    sigaction(SIGINT, &action, NULL);

    for (size_t i = 0; ; i++) {
        printf("%d\n", i);
        sleep(1);
    }
    return 0;
}
