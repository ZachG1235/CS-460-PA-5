// NAME - Avnish kumar sinha
// Further implementation of the sender handler for the chat client
// Date - 10/15/2023

#include "sender_handler.h"
#include "main.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>

// External reference to client information (defined in main.c)
extern struct {
    int socket_fd;
    struct {
        char *name;
    } *node;
} client_info;

void *sender_handler(void *arg) {
    char input_buffer[1024];  // Buffer for user input
    char output_buffer[1024]; // Buffer for formatted output to send
    bool shutdown = false;
    bool leave = false;

    while (1) {
        printf("Enter message ('JOIN', 'LEAVE', 'SHUTDOWN', 'SHUTDOWN_ALL' or any message): ");
        fflush(stdout);  // Ensure prompt is displayed immediately
        
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            printf("\nInput error or EOF encountered. Exiting.\n");
            break;  // Exit loop on input error
        }

        // Remove newline character from input if present
        input_buffer[strcspn(input_buffer, "\n")] = 0;

        // Skip empty input
        if (strlen(input_buffer) == 0) {
            continue;
        }

        // Handle special commands
        if (strcmp(input_buffer, "JOIN") == 0) {
            if(leave) {
                snprintf(output_buffer, sizeof(output_buffer), "JOIN:%s:%s", client_info.node->name, "RE-JOIN");
                leave = false;
            } else {
                snprintf(output_buffer, sizeof(output_buffer), "JOIN:%s", client_info.node->name);
            }
        } else if (strcmp(input_buffer, "LEAVE") == 0) {
            snprintf(output_buffer, sizeof(output_buffer), "LEAVE:%s", client_info.node->name);
            leave = true;
        } else if (strcmp(input_buffer, "SHUTDOWN") == 0) {
            snprintf(output_buffer, sizeof(output_buffer), "SHUTDOWN:%s", client_info.node->name);
            shutdown = true;
        } else if (strcmp(input_buffer, "SHUTDOWN_ALL") == 0) {
            snprintf(output_buffer, sizeof(output_buffer), "SHUTDOWN_ALL:%s", client_info.node->name);
            shutdown = true;
        } 
        else {
            // Regular message
            if(!leave) {
                snprintf(output_buffer, sizeof(output_buffer), "NOTE:%s:%s", client_info.node->name, input_buffer);
            } else {
                snprintf(output_buffer, sizeof(output_buffer), "NOTE:%s:%s", client_info.node->name, "SKIP");
            }
        }

        // Send the message to the server
        if (send(client_info.socket_fd, output_buffer, strlen(output_buffer), 0) < 0) {
            perror("send failed");
            exit(EXIT_FAILURE);
        }

        // Exit if shutdown command was sent
        if (shutdown) {
            printf("Shutting down client...\n");
            exit(EXIT_SUCCESS);
        }
    }

    return NULL;
}
