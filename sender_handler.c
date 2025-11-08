//NAME - Avnish 

// include statements
#include "sender_handler.h"

/* ===== function implementation ===== */
/*
 * Handles outgoing messages from user to server. Runs in separate thread
 * to continuously process user input and send formatted messages to server.
 * Manages chat session state and protocol commands.
 * Returns NULL on completion.
*/
void *sender_handler(void *arg) 
{
    // initialize variables
        // input buffer for user input
        // output buffer for formatted messages
        // shutdown flag
        // leave status flag
    
    // while true (continuous input loop)
        // display prompt for user input
        // get user input from stdin
        // if input error, break from loop
        
        // remove newline character from input
        
        // check input type and format appropriate message:
            // if JOIN command:
                // if previously left, format as rejoin message
                // else format as initial join message
                // set leave status to false
            // else if LEAVE command:
                // format leave message with username
                // set leave status to true
            // else if SHUTDOWN command:
                // format shutdown message
                // set shutdown flag
            // else if SHUTDOWN_ALL command:
                // format shutdown all message
                // set shutdown flag
            // else (regular message):
                // if not in leave state, format as note message
                // else format as skip message
        
        // send formatted message to server through socket
        // check for send errors, exit on failure
        
        // if shutdown flag set, exit successfully
    
    // return NULL
}
