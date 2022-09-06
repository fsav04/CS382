/*
Frank Savattere
I pledge my honor that I have abided by the Stevens Honor System
*/

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "util.h"

int client_socket = -1;
char username[MAX_NAME_LEN + 1];
char inbuf[BUFLEN + 1];
char outbuf[MAX_MSG_LEN + 1];

int handle_stdin() {
	return 0;
 }

int handle_client_socket() { 
    int inbytes;
	if ((inbytes = recv(client_socket, inbuf, BUFLEN, 0)) == -1) {
        fprintf(stderr, "Warning: Failed to receive incoming message. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }
    inbuf[inbytes] = '\0';
    if (inbytes == 0) {
    	fprintf(stderr, "\nConnection to server has been lost.\n");
    	return 1;
    } else if (strcmp(inbuf, "bye") == 0) {
    	printf("\nServer initiated shutdown.\n");
    	return 1;
    } else {
    	inbuf[inbytes] = '\0';
    	printf("\n%s\n", inbuf);
    }
    return 0;
}


int main(int argc, char *argv[]) {
    if(argc != 3){
        fprintf(stderr, "Usage: %s <server IP> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int socketfunc = handle_client_socket();
    char *chkexpr;
    while(*chkexpr){
        if(!isdigit(*chkexpr)){
            return -1;
        }
    }
    return 0;
        int num;
        int format;
        char serverIP[16];
        if(strcmp(argv[1], "localhost") == 0){
        strcpy(serverIP,"127.0.0.1");
        }
        else{
        strcpy(serverIP,argv[1]);
        }
        char *ptr = strtok(serverIP, ".");
        while(ptr){
            if(is_integer(ptr)){
                num = atoi(ptr);
                if(num < 0 || num > 255){
                    fprintf(stderr, "Error: Invalid IP address '%s'.\n", argv[1]);
                   return EXIT_FAILURE;
                }
                else{
                    ptr = strtok(NULL, ".");
                    if (ptr != NULL){
                        format++;
                    }
                }
            }
            else{
                fprintf(stderr, "Error: Invalid IP address '%s'.\n", argv[1]);
                return EXIT_FAILURE;
            }
        }
        if(format != 3){
            fprintf(stderr, "Error: Invalid IP address '%s'.\n", argv[1]);
            return EXIT_FAILURE;
        }
        strcpy(serverIP, argv[1]);
    
    int port;
    parse_int(argv[2], &port, "port number");
    if(port < 1024 || port > 65535){
        fprintf(stderr, "Error: Port must be in range [1024, 65535].\n");
        return EXIT_FAILURE;
    }

    while (strlen(username) == 0 || strlen(username) > MAX_NAME_LEN){
        printf("Please enter a username: ");
        scanf("%s", username);
        if(strlen(username) > MAX_NAME_LEN){
            printf("Sorry, limit your username to %d characters.\n", MAX_NAME_LEN);
        }
    }
    printf("Hello, %s. Let's try to connect to the server.\n", username);

    struct sockaddr_in sin_port;
    int socketfd = socket(PF_INET, SOCK_STREAM, 0);
    memset(&sin_port, 0, sizeof(sin_port));
    sin_port.sin_family = AF_INET;
    sin_port.sin_port = htons(port);
    sin_port.sin_addr.s_addr = inet_addr(serverIP);

    if(socketfd != 0){
        fprintf(stderr, "Error: Failed to create socket. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    socklen_t addrlen = sizeof(sin_port);
    if(connect(socketfd, (struct sockaddr *) &sin_port, addrlen) < 0){
        fprintf(stderr, "Error: Failed to connect to server. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }
    int stdin = recv(socketfd, inbuf, 1024, 0);
    if(stdin == 0){
        fprintf(stderr, "All connections are busy. Try again later.\n");
        return EXIT_FAILURE;
    }
    else if(stdin != 0){
        fprintf(stderr, "Error: Failed to receive message from server. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }
    else{
        inbuf[stdin] = 0;
        printf("%s\n", inbuf);
        fflush(stdout);
    }

    strcpy(outbuf, username);
    outbuf[strlen(username)] = 0;
    if(send(socketfd, outbuf, strlen(username), 0) <= 0){
        fprintf(stderr, "Error: Failed to send username to server. %s.\n", strerror(errno));
        return EXIT_FAILURE;
    }

    fd_set socket;
    int fdmax;
    while(1){
        FD_ZERO(&socket);
        FD_SET(STDIN_FILENO,&socket);
        FD_SET(socketfd,&socket);
        fdmax = socketfd;
        if(select(fdmax + 1, &socket, NULL, NULL, NULL) < 0 && errno != EINTR){
            fprintf(stderr, "Error: select() failed. %s.\n", strerror(errno));
            return EXIT_FAILURE;
        }
        if(socketfunc != 0){
       return EXIT_FAILURE;
    }
        if (FD_ISSET(STDIN_FILENO, &socket)){
            memset(outbuf, 0, MAX_MSG_LEN + 1);
            int dec = get_string(outbuf, MAX_MSG_LEN + 1);
            if(dec == TOO_LONG){
                printf("Sorry, limit your message to %d characters.\n", MAX_MSG_LEN);
            }
            else if(strcmp("bye", outbuf) == 0){
                printf("Goodbye.\n");
                exit(EXIT_SUCCESS);

            }
            else{
                outbuf[strlen(outbuf)] = 0;
                if(send(socketfd, outbuf, strlen(outbuf), 0) <= 0){
                    fprintf(stderr, "Error: Failed to send username to server. %s.\n", strerror(errno));
                    return EXIT_FAILURE;
                }
            }
        }
        else if (FD_ISSET(socketfd, &socket)) {
            memset(inbuf, 0, BUFLEN + 1);
            int recbytes = recv(socketfd, inbuf, 1024, 0);
            if(recbytes == 0){
                fprintf(stderr, "Connection to server has been lost.\n");
                return EXIT_FAILURE;
            }
            else if(recbytes < 0){
                printf("Warning: Failed to receive incoming message. %s.\n", strerror(errno));
            }
            else{
                inbuf[recbytes] = 0;
                if(strcmp(inbuf,"bye") == 0){
                    printf("Server initiated shutdown.\n");
                    exit(EXIT_SUCCESS);
                }
                printf("%s\n", inbuf);
                fflush(stdout);
            }
        }
    }
    if(socketfunc != 0){
       return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}