// include statements
#include "message.h"

/* ===== function implementation ===== */
/*
 * Sends a message to a recipient. Takes in a message struct 
 * (casts as a void* to send over network) and size, then sends it through socket.
 * Returns bytes to indicate success or error. 
*/
ssize_t sendMessage(int socket, const void* messageToSend, size_t messageSize)
{
    // initialize variables
        // total bytes sent
        // current bytes sent

    // while the total bytes sent is less than the messageSize
        // set current bytes sent = send(); send through socket
        // check if the connection is closed, if so return -1
        // increment total bytes sent by bytes
    
    // after loop, return the total bytes sent
}

/*
 * Receives messages from socket, and then returns a MessageStruct 
 * that holds all the data of the sent message. 
 * Returns bytes to indicate success or error.
*/
ssize_t receiveMessage(int socket, void* messageBuffer, size_t messageSize)
{
    // initialize variables
        // total bytes received
        // current bytes
    
    // while the total bytes received is less than MessageSize
        // set current bytes = recv() ; receive throug socket
        // check if connection closed, if so return -1
        // increment total bytes received by current bytes 
    
    // after loop, return the total bytes received
}