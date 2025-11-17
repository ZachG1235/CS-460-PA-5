// NAME - Avnish kumar sinha
// Further implementation of the receiver handler for the chat client 
// Date - 10/15/2023

#include "message.h"
#include "receiver_handler.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

// External reference to client information (should be defined in main.c)
extern struct {
    int socket_fd;
    struct {
        char *name;
    } *node;
} client_info;

// This function runs in a separate thread to handle incoming messages
void *receiver_handler(void *arg) {
    char buffer[1024];  // Buffer to store incoming data
    int read_size;

    // Continuously listen for incoming messages
    while ((read_size = recv(client_info.socket_fd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[read_size] = '\0'; // Null-terminate the string
        
        // Check for server shutdown command
        if (strcmp(buffer, "SHUTDOWN_ALL") == 0) {
            printf("[Server] Shutdown command received.\n");
            fflush(stdout);  // Ensure output is displayed immediately
            exit(EXIT_SUCCESS);  // Exit the client as the server is shutting down
        }
        
        // Display received message
        printf("%s\n", buffer);
        printf("Enter message ('JOIN', 'LEAVE', 'SHUTDOWN', 'SHUTDOWN_ALL' or any message): ");
        fflush(stdout);  // Ensure prompt is displayed immediately
    }

    // Handle connection closure or errors
    if (read_size == 0) {
        printf("Server has closed the connection.\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
    } else if (read_size < 0) {
        perror("recv failed");
        exit(EXIT_FAILURE);
    }

    return NULL;
}
