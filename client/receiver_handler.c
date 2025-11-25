
// receiver_handler.c
#include "receiver_handler.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char *client_name; // declared in main.c

void *receiver_handler(void *arg) {
    int sockfd = *((int *)arg);
    char buffer[1024];
    int read_size;

    while ((read_size = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[read_size] = '\0';
        if (strcmp(buffer, "SHUTDOWN_ALL") == 0) {
            printf("[Server] Shutdown command received.\n");
            exit(EXIT_SUCCESS);
        }
        printf("%s\n", buffer);
        printf("Enter message ('JOIN', 'LEAVE', 'SHUTDOWN', 'SHUTDOWN_ALL' or any message): \n");
    }

    if (read_size == 0) {
        printf("Server has closed the connection.\n");
        exit(EXIT_SUCCESS);
    } else if (read_size == -1) {
        exit(EXIT_FAILURE);
    }

    return NULL;
}

