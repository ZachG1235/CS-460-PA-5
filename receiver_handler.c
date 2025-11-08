// NAME - Avnish

/*
 * PSEUDOCODE:
 * 
 * FILE: receiver_handler.c
 * PURPOSE: Handle incoming messages from server in separate thread
 * 
 * INCLUDE: necessary headers (message.h, receiver_handler.h, main.h, stdio.h, etc.)
 * 
 * FUNCTION receiver_handler(void *arg) RETURNS void*:
 *     DECLARE:
 *         buffer[1024] AS character array
 *         read_size AS integer
 *     
 *     WHILE TRUE:
 *         SET read_size = receive data from server socket into buffer
 *         
 *         IF read_size > 0:
 *             NULL-terminate buffer string
 *             
 *             IF buffer equals "SHUTDOWN_ALL":
 *                 PRINT "Server shutdown command received"
 *                 EXIT program successfully
 *             ENDIF
 *             
 *             PRINT received message
 *             PRINT prompt for next user input
 *             
 *         ELSE IF read_size == 0:
 *             PRINT "Server closed connection"
 *             EXIT program successfully
 *             
 *         ELSE IF read_size < 0:
 *             EXIT program with failure
 *         ENDIF
 *     ENDWHILE
 *     
 *     RETURN NULL
 * END FUNCTION
 */

#include "message.h"
#include "receiver_handler.h"
#include "main.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// This function runs in a separate thread to handle incoming messages
void *receiver_handler(void *arg) {
    char buffer[1024];  // Buffer to store incoming data
    int read_size;

    while ((read_size = recv(client_info.socket_fd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[read_size] = '\0'; // Null-terminate the string
        if (strcmp(buffer, "SHUTDOWN_ALL") == 0) {
            printf("[Server] Shutdown command received.\n");
            exit(EXIT_SUCCESS);  // Exit the client as the server is shutting down
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
