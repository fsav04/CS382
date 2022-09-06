#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>

#define BLUE "\x1b[34;1m"
#define DEFAULT "\x1b[0m"
#define MAX 1024

int main() {
char arr[1000];
char cwd[MAX];
while(1){
getcwd(cwd, sizeof(cwd));
printf("%s%s%s ", BLUE, cwd, DEFAULT);
fgets(arr, MAX, stdin);
if (strcmp(arr, "cd\n") == 0){
struct passwd *pw = getpwuid(getuid());
const char *homedir = pw->pw_dir; //get home directory
chdir(homedir); //change directory to home
}
else if (strcmp(arr, "cd") == 0){
    char str[MAX];
    strcpy(str, arr);
	int init_size = strlen(str);
	char delim[] = " ";

	char *ptr = strtok(str, delim);

	while(ptr != NULL)
	{
		ptr = strtok(NULL, delim);
	}
}
else if (strcmp(arr, "ls\n") == 0){
struct dirent *dp;
DIR *dir = opendir(".");
if (!dir){
    // printf("Error: Cannot change directory to %s. %s.\n", dp->d_name, stderr);
    printf("error");
}
while ((dp = readdir(dir)) != NULL){
    printf("%s\n", dp->d_name);
}
closedir(dir);
}
}
return 0;
}



