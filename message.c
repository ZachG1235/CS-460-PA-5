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
    size_t totalSent = 0;
        // current bytes sent
    ssize_t curBytesSent;

    // while the total bytes sent is less than the messageSize
    while (totalSent < curBytesSent)
    {
        // set current bytes sent = send(); send through socket
        curBytesSent = send(socket, (const char*)messageToSend + totalSent, messageSize - totalSent, 0);
        // check if the connection is closed, if so return -1
        if (curBytesSent <= 0)
        {
            return -1;
        }
        // increment total bytes sent by bytes
        totalSent += curBytesSent;
    }    
    // after loop, return the total bytes sent
    return totalSent;
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
    size_t totalReceived = 0;
        // current bytes
    ssize_t curBytesReceived;
    
    // while the total bytes received is less than MessageSize
    while (totalReceived < messageSize)
    {
        // set current bytes = recv() ; receive throug socket
        curBytesReceived = recv(socket, (char*)messageBuffer + totalReceived, messageSize - totalReceived, 0);
        // check if connection closed, if so return -1
        if (curBytesReceived <= 0)
        {
            return curBytesReceived;
        }
        // increment total bytes received by current bytes 
        totalReceived += curBytesReceived;
    }
    // after loop, return the total bytes received
    return totalReceived;
}