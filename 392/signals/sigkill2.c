/*** sigkill2.c ***/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#define N 5

void fork12() {
    pid_t pid[N];
    int   i;
    int   child_status;

    for (i = 0; i < N; i ++) {
        /* Child: Infinite Loop */
        if ((pid[i] = fork()) == 0) while(1);
    }

    for (i = 0; i < N; i ++) {
        printf("Killing process %d\n", pid[i]);
        kill(pid[i], SIGINT);
    }

    for (i = 0; i < N; i ++) {
        pid_t wpid = wait(&child_status);
        if (WIFEXITED(child_status))
            printf("Child %d terminated with exit status %d\n",
                    wpid, WEXITSTATUS(child_status));
        else printf("Child %d terminated abnormally\n", wpid);
    }
}

int main() {
    fork12();
    return 0;
}
