/*** demo1/server.c ***/
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {


    char* server_path = "/tmp/myfifo";
    mkfifo(server_path, 0666);

    char str[1024];
    int fd = open(server_path, O_WRONLY);
    int i;
    for (i = 0; read(0, str+i,1) != -1 && str[i] != '\n'; i++);
        
    write(fd, str, i+1);
    close(fd);

    return 0;
}