/*** sigkill3.c ***/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void sig_handler(int sig) {
    if (sig == SIGINT) printf("Meow!\n");
    else if (sig == SIGCHLD) {
        printf("Woof!\n");
        exit(EXIT_SUCCESS);
    }
}


int main() {
    pid_t pid;

    /* Installing signal handler */
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");
    if (signal(SIGCHLD, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGCHLD\n");

    if ((pid = fork()) == 0) {
        printf("I'm the child %d\nSending SIGINT now...\n", pid);
        kill(getppid(), SIGINT);
        sleep(2);
        printf("I'm done!\n");
    }
    else while (1);

    return 0;
}
