/*** sigblock2.c ***/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void catch_stop(int sig) {
    const char* signame = sys_signame[sig];
    printf("\n");
    for (int second = 5; second >= 0; second --) {
        printf("[sig%s] %d\n", signame, second);
        sleep(1);
    }
}

void install_handler() {
    struct sigaction setup_action;
    sigset_t block_mask;
    sigemptyset (&block_mask);
    /* Block other terminal-generated signals while handler runs. */
    sigaddset (&block_mask, SIGINT);
    sigaddset (&block_mask, SIGQUIT);
    setup_action.sa_handler =  catch_stop;
    setup_action.sa_mask    =  block_mask;
    setup_action.sa_flags   =  0;
    sigaction (SIGINT, &setup_action, NULL);
    sigaction (SIGQUIT,&setup_action, NULL);
}

int main() {
    install_handler();
    while (1);
    return 0;
}
