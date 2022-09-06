/*** sig2.c ***/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sig_handler(int signo) {
    switch (signo) {
        case SIGUSR1:
            printf("Received SIGUSR1...\n");
            sleep(10);
            printf("SIGUSER1 Not done yet...\n");
            sleep(10);
            printf("OK SIGUSER1 done!\n");
            break;
        case SIGUSR2:
            printf("Received SIGUSR2...\n");
            sleep(10);
            printf("SIGUSER2 Not done yet...\n");
            sleep(10);
            printf("OK SIGUSER2 done!\n");
    }
}

int main() {
    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR1\n");
    if (signal(SIGUSR2, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR2\n");

    while(1) sleep(1);

    return 0;
}
