//NAME - Avnish 

/*
 * PSEUDOCODE:
 * 
 * FILE: sender_handler.c  
 * PURPOSE: Handle outgoing messages to server based on user input
 * 
 * INCLUDE: necessary headers (sender_handler.h, main.h, message.h, etc.)
 * 
 * FUNCTION sender_handler(void *arg) RETURNS void*:
 *     DECLARE:
 *         input_buffer[1024] AS character array
 *         output_buffer[1024] AS character array
 *         shutdown AS boolean = false
 *         leave AS boolean = false
 *     
 *     WHILE TRUE:
 *         PRINT prompt for user input
 *         
 *         GET user input into input_buffer
 *         IF input error:
 *             BREAK from loop
 *         ENDIF
 *         
 *         REMOVE newline from input_buffer
 *         
 *         // Handle special commands
 *         IF input equals "JOIN":
 *             IF leave is true:
 *                 FORMAT output_buffer as "JOIN:username:RE-JOIN"
 *                 SET leave = false
 *             ELSE:
 *                 FORMAT output_buffer as "JOIN:username"
 *             ENDIF
 *             
 *         ELSE IF input equals "LEAVE":
 *             FORMAT output_buffer as "LEAVE:username"
 *             SET leave = true
 *             
 *         ELSE IF input equals "SHUTDOWN":
 *             FORMAT output_buffer as "SHUTDOWN:username"
 *             SET shutdown = true
 *             
 *         ELSE IF input equals "SHUTDOWN_ALL":
 *             FORMAT output_buffer as "SHUTDOWN_ALL:username"
 *             SET shutdown = true
 *             
 *         ELSE: // Regular message
 *             IF NOT leave:
 *                 FORMAT output_buffer as "NOTE:username:message"
 *             ELSE:
 *                 FORMAT output_buffer as "NOTE:username:SKIP"
 *             ENDIF
 *         ENDIF
 *         
 *         // Send message to server
 *         SEND output_buffer to server socket
 *         IF send fails:
 *             PRINT error
 *             EXIT with failure
 *         ENDIF
 *         
 *         IF shutdown is true:
 *             EXIT successfully
 *         ENDIF
 *     ENDWHILE
 *     
 *     RETURN NULL
 * END FUNCTION
 */

#include "sender_handler.h"
#include "main.h"
#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

void *sender_handler(void *arg) {
    char input_buffer[1024];  // Buffer for user input
    char output_buffer[1024]; // Buffer for formatted output to send
    bool shutdown = false;
    bool leave = false;

    while (1) {
        printf("Enter message ('JOIN', 'LEAVE', 'SHUTDOWN', 'SHUTDOWN_ALL' or any message): \n");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            break;  // Exit loop on input error
        }

        // Remove newline character from input if present
        input_buffer[strcspn(input_buffer, "\n")] = 0;

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

        if (shutdown)
            exit(EXIT_SUCCESS);
        // if(leave)
        //     return (void*)2;

    }

    return NULL;
}