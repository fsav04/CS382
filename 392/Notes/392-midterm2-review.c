/* Midterm 2 Review 
When fork() fails it returns -1
execlp() is for lists
execvp() is for vectors

exec and fork differences- 
fork creates new
exec replaces
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>
#include <signal.h>
int main() {

pid_t children[5];
 for (size_t i = 0; i < 5; i++) {
 if ((children[i] = fork()) == 0) {
 printf("I'm child %d in group %d.\n", getpid(), getpgrp());
 wait(1);
 exit(EXIT_SUCCESS);
 }
 }
 printf("I'm parent %d, in group %d\n", getpid(), getpgrp());
 exit(EXIT_SUCCESS);
 }

