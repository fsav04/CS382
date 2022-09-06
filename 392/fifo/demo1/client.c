/*** demo1/client.c ***/
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

    char* server_path = "/tmp/myfifo";

    char str[1024];
    int fd = open(server_path, O_RDONLY);

    int len = 0;
    for (len = 0; read(fd, str+len,1) != -1 && str[len] != '\n'; len ++);

    for (size_t j = 0; j < len; j ++) write(1, str+j, 1);

    close(fd);
    return 0;
}
