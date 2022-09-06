/*** pgroup.c ***/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t children[5];
    for (size_t i = 0; i < 5; i++) {
        if ((children[i] = fork()) == 0) {
            printf("I'm child %d in group %d.\n", getpid(), getpgrp());
            exit(EXIT_SUCCESS);
        }
    }
    printf("I'm parent %d, in group %d\n", getpid(), getpgrp());
    exit(EXIT_SUCCESS);
}
