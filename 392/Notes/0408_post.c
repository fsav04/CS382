#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1


/*
    Child 1 sends a msg "Hello" to Child 2;
    Child 2 receives msg "Hello" and adds "World",
    then sends it to the Parent.

    Neither child 1 and 2 knows about pipes,
    so they used printf() and scanf().
    You need to figure out how to redirect
    the messages to the pipes.
*/


int main(int argc, char const *argv[]) {

    pid_t ret[2];
    int c1_c2[2];
    int c2_p[2];

    pipe(c1_c2);
    pipe(c2_p);

    ret[0] = fork();
    if (ret[0] == 0) {
    /* Your code here */

        printf("Hello");
        exit(0);
    }

    ret[1] = fork();
    if (ret[1] == 0) {

        /* Your code here */

        char arr[1024] = {0};
        scanf("%s", arr);
        printf("%s World!\n", arr);
        exit(0);
    }


    /* Your code here */


    return 0;
}
