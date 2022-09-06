/*** pgroup2.c ***/
/*** modified from
     https://www.ibm.com/docs/en/SSLTBW_2.2.0/com.ibm.zos.v2r2.bpxbd00/rtgtpg.htm
     ***/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status;

    if (fork() == 0) {
        if (fork() == 0) {
            printf("grandchild's pid is %d, process group id is %d\n",
                    (int) getpid(), (int) getpgrp());
            exit(EXIT_SUCCESS);
        }
        printf("child's pid is %d, process group id is %d\n",
                (int) getpid(), (int) getpgrp());
        wait(&status);
        exit(EXIT_SUCCESS);
    }
    printf("parent's pid is %d, process group id is %d\n",
            (int) getpid(), (int) getpgrp());
    printf("the parent's parent's pid is %d\n", (int) getppid());
    wait(&status);
    exit(EXIT_SUCCESS);
}
