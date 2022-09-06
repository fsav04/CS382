/*Frank Savattere
I pledge my honor that I have abided by the Stevens Honor System*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


#define READ_END 0
#define WRITE_END 1

int main(int argc, char const *argv[]) {

     char* usage = "Usage: ./spfind -d <directory> -p <permissions string> \n";
    if (argc != 5){
        write(2, usage, strlen(usage));
        return EXIT_FAILURE;
    }
    for (int i = 0; i < strlen(argv[4]); i++){
        if((argv[4][i] != 'r') && (argv[4][i] != 'w') && (argv[4][i] != 'x') && (argv[4][i] != '-')){
        printf("Error: Permissions string '%s' is invalid.\n", argv[4]);
        return EXIT_FAILURE;
        }
    }

    pid_t ret[2];
    int c1_c2[2];
    int c2_p[2];

    pipe(c1_c2);
    pipe(c2_p);

    ret[0] = fork();
    if (ret[0] == 0) {
        if(close(c1_c2[WRITE_END]) != -1){
            close(c1_c2[WRITE_END]);
        }
        else{
            printf("Error");
            return EXIT_FAILURE;
        }
        if(dup2(c1_c2[READ_END], 0) != -1){
            dup2(c1_c2[READ_END], 0);
        }
        else{
            printf("Error");
            return EXIT_FAILURE;
        }
        if(close(c2_p[READ_END]) != -1){
            close(c2_p[READ_END]);
        }
        else{
            printf("Error");
            return EXIT_FAILURE;
        }
        if(dup2(c2_p[WRITE_END], 1) != -1){
            dup2(c2_p[WRITE_END], 1);
        }
        else{
            printf("Error");
            return EXIT_FAILURE;
        }
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
        if(close(c1_c2[WRITE_END]) != -1){
            close(c1_c2[WRITE_END]);
        }
        else{
            printf("Error");
            return EXIT_FAILURE;
        }
        if(dup2(c1_c2[READ_END], 0) != -1){
            dup2(c1_c2[READ_END], 0);
        }
        else{
            printf("Error");
            return EXIT_FAILURE;
        }
        if(close(c2_p[READ_END]) != -1){
            close(c2_p[READ_END]);
        }
        else{
            printf("Error");
            return EXIT_FAILURE;
        }
        if(dup2(c2_p[WRITE_END], 1) != -1){
            dup2(c2_p[WRITE_END], 1);
        }
        else{
            printf("Error");
            return EXIT_FAILURE;
        }
        char arr[1024] = {0};
        if (execlp("sort", "sort", 0, NULL) == -1){
            char* sortError = "Error: sort failed";
            write(2, sortError, strlen(sortError));
            return EXIT_FAILURE;
        }
        else{
            printf("Error");
            return EXIT_FAILURE;
        }
        exit(0);
    }

    if(close(c2_p[WRITE_END]) != -1){
        close(c2_p[WRITE_END]);
    }
    else{
            printf("Error");
            return EXIT_FAILURE;
        }
    if(close(c1_c2[WRITE_END]) != -1){
        close(c1_c2[WRITE_END]);
    }
    else{
            printf("Error");
            return EXIT_FAILURE;
        }
    if(close(c1_c2[READ_END]) != -1){
        close(c1_c2[READ_END]);
    }
    else{
            printf("Error");
            return EXIT_FAILURE;
        }

    char c = 0;
    int line = 0;
    while( read(c2_p[READ_END], &c, 1) != 0 ) {
        printf("%c", c);
        if (c == '\n'){
            line++;
        }
    }

    printf("Total Matches: %d\n", line);
    while(wait(NULL) > 0);

    
    
    return 0;
}
