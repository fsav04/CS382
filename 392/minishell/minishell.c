/*
Frank Savattere
I pledge my honor that I have abided by the Stevens Honor System
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

#define BLUE "\x1b[34;1m"
#define DEFAULT "\x1b[0m"
#define MAX 1024

int checkChar(char* str){
	int hasspace = 1;
	int count;
	for(int i = 0; i < strlen(str); i++){
		if(str[i] == ' '){
			count++;
			if(count == 2){
				hasspace = 0;
				return hasspace;
			}
		}
}
	return hasspace;
}


static volatile sig_atomic_t interrupted = 0;

void sigHandler(int sig){
	printf("\n");
    interrupted = 1;
    fflush(stdout);
	exit(0);
}

char cmd[MAX] = "";
int changedir(char* dir){ //changes directory
if((strcmp(dir, "~") == 0) || strcmp(dir, "cd\n") == 0){
char arr[1000];
char cwd[MAX];
getcwd(cwd, sizeof(cwd));
struct passwd *pw = getpwuid(getuid());
const char *homedir = pw->pw_dir; //get home directory
chdir(homedir); //change directory to home
return 0;
}
else if(chdir(dir) == 0){
chdir(dir);
return 0;
}
return -1;
}



int main(int argc, char *argv[]){
	if (argc != 1){
		printf("Usage: %s\n", argv[0]);
		return EXIT_FAILURE;
	}
	struct sigaction sa;
    sa.sa_handler = sigHandler;
	
	if (sigaction(SIGINT, &sa, NULL) < 0){
            fprintf(stderr, "Error: Cannot reigster signal handler. %s. \n", strerror(errno));
			memset(cmd, 0, MAX);
	}
	
	while(1){
		char cwd[MAX];
		if(getcwd(cwd, sizeof(cwd)) == NULL){
			fprintf(stderr, "Error: Cannot get current working directory. %s.\n", strerror(errno));
			memset(cmd, 0, MAX);
			return EXIT_FAILURE;
		}
		memset(cmd, 0, strlen(cmd));
		printf("%s[%s%s%s]> ",DEFAULT, BLUE, cwd, DEFAULT);
		while(1){
			char cnew = getchar();
			if(cnew == '\n'){
				break;
			}else{
				strncat(cmd, &cnew, 1);
			}
			
		}
		if(strcmp(cmd, "exit") == 0){
			break;
		}else if((strcmp(cmd, "cd") == 0)||(strncmp(cmd, "cd ", 3) == 0)){
			
			char *cd;
			cd = strchr(cmd, 'd') + 2;
			if(strcmp(cmd, "cd") == 0){
				cd = "~";
			}
			int cdr = changedir(cd);
			if(cdr == -1){
				char* cdcpy = cd;
				if(checkChar(cdcpy) == 0){
					printf("Error: Too many arguments to cd.\n");
					memset(cmd, 0, MAX);
				}
				else{
				printf("Error: Cannot change directory to '%s'. %s.\n", (strchr(cmd, 'd')+2),strerror(errno));
				memset(cmd, 0, MAX);
				}
			}
		}
		else{
			pid_t pid;
			if((pid = fork()) < 0){
				fprintf(stderr, "Error: fork() failed. %s.\n", strerror(errno));
				memset(cmd, 0, MAX);
				return EXIT_FAILURE;
			}
			if(pid == 0){
				char *str[MAX];
				//char* strcpy = (char *)malloc(MAX);
				char delim[] = " ";
				int i = 0;
				
				char *ptr = strtok(cmd, delim);
				while(ptr != NULL){
					str[i] = ptr;
					ptr = strtok(NULL, delim);
					i++;
				}
				str[i] = NULL;
				if((execvp(str[0], str)) < 0){
					fprintf(stderr, "Error: exec() failed. %s.\n", strerror(errno));
					memset(cmd, 0, MAX);
					return EXIT_FAILURE;
				}
				//free(strcpy);
			}
			else{
				if(wait(NULL) < 0){
					fprintf(stderr, "Error: wait() failed. %s.\n", strerror(errno));
					memset(cmd, 0, MAX);
					return EXIT_FAILURE;
				}
			}	
		}

	}
	memset(cmd, 0, strlen(cmd));
	return EXIT_SUCCESS;
}