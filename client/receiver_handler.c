
// NAME - Avnish

// include statements
#include "message.h"

/* ===== function implementation ===== */
/*
 * Handles incoming messages from server to client. Runs in separate thread
 * to continuously listen for server messages and display them to user.
 * Manages connection state and handles server commands.
 * Returns NULL on completion.
*/
void *receiverHandler(void *arg) 
{
    // initialize variables
        // buffer for incoming data
        // read size variable
    
    // while receiving data from server socket
        // set read size = receive data from server into buffer
        // if read size > 0:
            // null-terminate the received string
            
            // check for special server commands:
                // if message is "SHUTDOWN ALL":
                    // display shutdown notification
                    // exit program successfully
            
            // display received message to user
            // display prompt for next user input
            
        // else if read size == 0:
            // display "server closed connection"
            // exit program successfully
            
        // else if read size < 0:
            // exit program with failure
    
    // return NULL
}

