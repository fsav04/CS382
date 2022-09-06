#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
    if (signal(SIGINT, sig_handler) == SIG){
        printf("\ncan't catch SIGINT\n");
        for (size_t i = 1; ; i++){
            printf("%ld\n", i)
        }
    }
}