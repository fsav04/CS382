#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>

int output(char* filename, char format, void* data);
int input(char* filename, char format, void* data);
int clean();
