#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

int perms(char* perms){
    if(strlen(perms) != 9){
        for (int i = 0, j = 0; i < 9; i++){
            char cur;
            if (j == 0){
                cur = 'r';
                j++;
            }
            else if (j == 1){
                cur = 'w';
                j++;
        }
            else{
                cur = 'x';
                j = 0;
            }
            char check =*(perms + i);
            if (check != cur && check != '-'){
                return 1;
            }
        }
        return 0;
    }
}
int main(int argc, char const *argv[]) {
    if (argc != 5){
        char* usage = "Usage: ./spfind -d <directory> -p <permissions string> \n";
        write(2, usage, strlen(usage));
        return EXIT_FAILURE;
    }
    else if (!perms(argv[4])){
        char* bad = argv[4];
        char* start = "Error: Perrmsion string '";
        char* end = "' is invalid \n";
        return EXIT_FAILURE;
    }
    pid_t ret[2];
    int c1_c2[2];
    int c2_p[2];

    pipe(c1_c2);
    pipe(c2_p);

    ret[0] = fork();
    if (ret[0] == 0) {
        /* c1 */
        close(c1_c2[READ_END]);
        dup2(c1_c2[WRITE_END], 1);
        close(c2_p[WRITE_END]);
        close(c2_p[READ_END]);
        char* pfinder = "./pfind";
        argv[0] = pfinder;
        if(execvp(argv[0], argv) == -1){
            char* pfError = "Error: pfind failed.";
            write(2, pfError, strlen(pfError));
            return EXIT_FAILURE;
        }
        exit(0);
    }

    ret[1] = fork();
    if (ret[1] == 0) {
        /* c2 */
        close(c1_c2[WRITE_END]);
        dup2(c1_c2[READ_END], 0);
        close(c2_p[READ_END]);
        dup2(c2_p[WRITE_END], 1);
        char arr[1024] = {0};
        if (execlp("sort", "sort", 0, NULL) == -1){
            char* sortError = "Error: sort failed"
            write(2, sortError, strlen(sortError));
            return EXIT_FAILURE;
        }
        exit(0);
    }

    close(c2_p[WRITE_END]);
    close(c1_c2[WRITE_END]);
    close(c1_c2[READ_END]);

    char c = 0;
    int line = 0;
    while( read(c2_p[READ_END], &c, 1) != 0 ) {
        printf("[%c]", c);
    }
    printf("\n");

    while(wait(NULL) > 0);
    
    return 0;
}
