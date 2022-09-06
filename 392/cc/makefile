CC = gcc
FLAGS = -Wall -Werror -pedantic-errors -o

all: client.c

client.c:
	$(CC) $(FLAGS) chatclient chatclient.c
server.c:
	$(CC) $(FLAGS) chatserver chatserver.c
clean:
	rm -f chatclient chatclient.exe chatserver chatserver.exe