#ifndef message_h
#define message_h

/* additional libraries */
#include <unistd.h>
#include "chat_node.h"

/* ===== data types ===== */

// MessageType enum that can describe each message type (JOIN, LEAVE, ECT.)
enum MessageType
{
    // join, leave, shutdown, note 
    JOIN,
    LEAVE,
    SHUTDOWN,
    NOTE
};

// message struct that details whats in a message
// struct MessageStruct
typedef struct messageStruct
{
    // message type: holds message type (enum)
    enum MessageType msgType;
    // client struct: holds client sending message (client struct)
    ChatNode senderInfo;
    // message content: holds the string of a message (char array)
    char msgContent[255];
} MessageStruct;


/* ===== function prototypes ===== */

/* 
 * Sends a message to a recipient. Takes in a message struct 
 * (casts as a void* to send over network) and size, then sends it through socket.
 * Returns bytes to indicate success or error. 
*/
ssize_t sendMessage(int socket, const void* messageToSend, size_t messageSize);

/*
 * Receives messages from socket, and then returns a MessageStruct 
 * that holds all the data of the sent message. 
 * Returns bytes to indicate success or error.
*/
ssize_t receiveMessage(int socket, void* messageBuffer, size_t messageSize);

#endif // message_h