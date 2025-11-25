
#include "sender_handler.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

extern char *client_name; // declared in main.c

void *sender_handler(void *arg) {
    int sockfd = *((int *)arg);
    char input_buffer[1024];
    char output_buffer[1024];
    bool shutdown = false;
    bool leave = false;

    while (1) {
        printf("Enter message ('JOIN', 'LEAVE', 'SHUTDOWN', 'SHUTDOWN_ALL' or any message): \n");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            break;
        }
        input_buffer[strcspn(input_buffer, "\n")] = 0;

        if (strcmp(input_buffer, "JOIN") == 0) {
            if (leave) {
                snprintf(output_buffer, sizeof(output_buffer), "JOIN:%s:%s", client_name, "RE-JOIN");
                leave = false;
            } else {
                snprintf(output_buffer, sizeof(output_buffer), "JOIN:%s", client_name);
            }
        } else if (strcmp(input_buffer, "LEAVE") == 0) {
            snprintf(output_buffer, sizeof(output_buffer), "LEAVE:%s", client_name);
            leave = true;
        } else if (strcmp(input_buffer, "SHUTDOWN") == 0) {
            snprintf(output_buffer, sizeof(output_buffer), "SHUTDOWN:%s", client_name);
            shutdown = true;
        } else if (strcmp(input_buffer, "SHUTDOWN_ALL") == 0) {
            snprintf(output_buffer, sizeof(output_buffer), "SHUTDOWN_ALL:%s", client_name);
            shutdown = true;
        } else {
            if (!leave) {
                snprintf(output_buffer, sizeof(output_buffer), "NOTE:%s:%s", client_name, input_buffer);
            } else {
                snprintf(output_buffer, sizeof(output_buffer), "NOTE:%s:%s", client_name, "SKIP");
            }
        }

        if (send(sockfd, output_buffer, strlen(output_buffer), 0) < 0) {
            perror("send failed");
            exit(EXIT_FAILURE);
        }

        if (shutdown)
            exit(EXIT_SUCCESS);
    }

    return NULL;
}
